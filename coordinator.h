#ifndef COORDINATOR_H
#define COORDINATOR_H

/**
 * The `coordinator` class is responsible for managing the game state and making decisions during gameplay.
 * It uses a collection of `matchbox` objects, each representing a possible game state.
 * The `matchbox` objects are hashed and stored in a vector for efficient searching.
 * The 'coordinator' is making decisions based on the current game state and the possible moves in the current matchbox.
 * The decisions are made using a random number generator to pick a move based on the weights of the possible moves.
 * After the game endes the `coordinator` updates the weights of the possible moves in the matchboxes based on the outcome of the game.
 * Therfore, if the outcome is positive, the weights of the moves that were played are incremented, and if the outcome is negative, the weights of the moves that were played are decremented.
 * so, the `coordinator` learns from its mistakes and tries to avoid them in the future.
 * After each run, the `coordinator` saves the current state of the matchboxes to a file, so that it can be used in the next run.
 */

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include <ctime>

#include "matchbox.h"

using namespace std;


class coordinator
{
private:
    // Declare a static vector of matchbox pointers. This vector will hold all possible game states which are hashed to make easier for searching.
    static vector <matchbox*> collectionOfMatchBoxes;
    // Declare a static vector of pairs. Each pair contains a move and its corresponding hash index which represents the place of the matchbox.
    static vector <pair<int,int>> movesPlayedPerGame;
    
public:

    static void getMatchBoxes(); // This function reads the game patterns from a file and stores them in collectionOfMatchBoxes.
    static int getHashingIndex(matchbox* currMatchBox); // This function calculates a hash index for a given matchbox based on its current board state.
    static matchbox* searchMatchBox(board currBoard); // This function searches for a matchbox in the collection that matches the current board state.
    static int pickMove( board currBoard); // This function chooses the next move to play based on the current board state. it depends on searchMatchBox and make a random move statisitcally based on the matchbox possiable moves.
    static void updateMatchBox(int win); // This function updates the matchbox objects based on the outcome of the game.
    static void saveToFile(); // This function saves the current state of collectionOfMatchBoxes to a file.
};

vector <matchbox*> coordinator::collectionOfMatchBoxes(8000);

vector <pair<int,int>> coordinator::movesPlayedPerGame;

int coordinator::getHashingIndex(matchbox* currMatchBox){
        int hashingIndex =0;
       
        if (currMatchBox != nullptr)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    hashingIndex = hashingIndex + (currMatchBox->getCurrBoard()[i][j] * ( i +j ));
                }
                
            } 
        }
        



        return (hashingIndex/2) % 8000;  

        
    }

void coordinator::getMatchBoxes(){
    // Open the file "patterns.dat" for reading.
    ifstream file("patterns.dat");
    // If the file failed to open, print an error message and return.
    if (!file.is_open()) {
        cout << "Failed to open patterns.dat" << endl;
        return;
    }

    // Declare a string to hold each line of the file.
    string line;
    // Declare a counter to keep track of the current matchbox.
    int counter = 0;
    // Read the file line by line.
    while (getline(file,line))
    {
        // Create a stringstream from the line for easy parsing.
        stringstream ss(line);
        // Declare a new matchbox.
        matchbox* tempMatchBox = new matchbox;

        // Read the current board state from the stringstream.
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                char temp;
                ss >> temp;
                // Set the board state in the matchbox.
                tempMatchBox->setCurrBoard(i,j,temp);
            }
        }

        // Read the possible moves from the stringstream.
        for (int i = 0; i < 9; i++)
        {
            int first;
            int second;

            ss>> first;
            ss>> second;

            // Set the possible moves in the matchbox.
            tempMatchBox->setPossiableMoves(i,first,second);
        }

        // Add the matchbox to the collection.
        collectionOfMatchBoxes[counter] = tempMatchBox;
        // Increment the counter.
        counter++;
    }
    // Close the file.
    file.close();

    // Create a temporary collection of matchboxes.
    vector <matchbox*> tempCollectionOfMatchBoxes;
    // Resize the temporary collection to 8000.
    tempCollectionOfMatchBoxes.resize(8000);

    // Rehash the matchboxes based on their board state.
    for (int i = 0; i < 8000; i++)
    {
        // Get the hashing index for the matchbox.
        int hashingIndex = getHashingIndex(collectionOfMatchBoxes[i]) ;
        // If the hashing index is already taken, increment it until an empty spot is found.
        while (tempCollectionOfMatchBoxes[hashingIndex] != nullptr)
        {
            hashingIndex++;
        }
        
        // Add the matchbox to the temporary collection at the hashing index.
        tempCollectionOfMatchBoxes[hashingIndex] = collectionOfMatchBoxes[i];
    }

    // Replace the original collection with the rehashed collection.
    collectionOfMatchBoxes = tempCollectionOfMatchBoxes;
}

matchbox* coordinator::searchMatchBox(board Board){
    matchbox* currMatchBox = new matchbox;
    currMatchBox->setCurrBoard(Board);
    int hashingIndex = getHashingIndex(currMatchBox);
    while (collectionOfMatchBoxes[hashingIndex] != nullptr)
    {
        if (collectionOfMatchBoxes[hashingIndex]->getCurrBoard() == Board)
        {
            return collectionOfMatchBoxes[hashingIndex];
        }
        hashingIndex++;
    }
    
    return nullptr;
    
}

int coordinator::pickMove(board currBoard){
    // Declare a vector to hold the weights of the possible moves.
    vector <int> moveWeights;
    // Find the matchbox that matches the current board state.
    matchbox* currMatchBox = searchMatchBox(currBoard);
    // Get the possible moves from the current matchbox.
    vector<pair<int,int>> currPossiableMoves = currMatchBox->getPossiableMoves();

    
    // For each possible move...
    for (int i = 0; i < 9; i++)
    {
        // ...add the move to the moveWeights vector as many times as its weight. This will make it more likely to be picked.
        for (int j = 0; j < currPossiableMoves[i].second; j++)
        {
            moveWeights.push_back(currPossiableMoves[i].first);
        }
    }

    // Pick a random move from the moveWeights vector.
    srand(time(0));
    int random = rand() % moveWeights.size();
    int move = moveWeights[random];

    return move;
}

void coordinator::updateMatchBox(int win){

    cout << "Updating Matchboxes...." << endl;
    int s = movesPlayedPerGame.size();

    // If the game was a loss...
    if (win == -1)
    {
        // ...for each move that was played...
        for (int i = 0; i < s; i++)
        {
            
            int hashingIndex = movesPlayedPerGame[i].second;
            matchbox* currMatchBox = collectionOfMatchBoxes[hashingIndex];
            // get the possible moves from the matchbox.
            nextMoves currPossiableMoves = currMatchBox->getPossiableMoves();

            // For each possible move...
            for (int j = 0; j < 9; j++)
            {
                // ...if the move matches the one that was played...
                if (currPossiableMoves[j].first == movesPlayedPerGame[i].first)
                {
                    // ...decrement the weight of the move,
                    currPossiableMoves[j].second--;
                    // ...update the possible moves in the matchbox,
                    currMatchBox->setPossiableMoves(currPossiableMoves);
                    // ...and update the matchbox in the collection.
                    collectionOfMatchBoxes[hashingIndex] = currMatchBox;
                    break;
                }
            }
        }
    }

    // If the game was a win...
    else if(win == 1){

        for (int i = 0; i < s; i++)
        {

            int hashingIndex = movesPlayedPerGame[i].second;
            matchbox* currMatchBox = collectionOfMatchBoxes[hashingIndex];
            //and get the possible moves from the matchbox.
            nextMoves currPossiableMoves = currMatchBox->getPossiableMoves();

            for (int j = 0; j < 9; j++)
            {
                // ...if the move matches the one that was played...
                if (currPossiableMoves[j].first == movesPlayedPerGame[i].first)
                {
                    // ...increment the weight of the move by 2,
                    currPossiableMoves[j].second = currPossiableMoves[j].second + 2;
                    // ...update the possible moves in the matchbox,
                    currMatchBox->setPossiableMoves(currPossiableMoves);
                    // ...and update the matchbox in the collection.
                    collectionOfMatchBoxes[hashingIndex] = currMatchBox;
                    break;
                }
            }
        }
    }

    // If the game was a draw...
    else{

        for (int i = 0; i < s; i++)
        {

            int hashingIndex = movesPlayedPerGame[i].second;
            matchbox* currMatchBox = collectionOfMatchBoxes[hashingIndex];
            // get the possible moves from the matchbox.
            nextMoves currPossiableMoves = currMatchBox->getPossiableMoves();


            for (int j = 0; j < 9; j++)
            {
                // ...if the move matches the one that was played...
                if (currPossiableMoves[j].first == movesPlayedPerGame[i].first)
                {
                    // ...increment the weight of the move,
                    currPossiableMoves[j].second++;
                    // ...update the possible moves in the matchbox,
                    currMatchBox->setPossiableMoves(currPossiableMoves);
                    // ...and update the matchbox in the collection.
                    collectionOfMatchBoxes[hashingIndex] = currMatchBox;
                    break;
                }
            }
        }
    }

    cout << "good game. I will learn from it!" << endl;
}

void coordinator::saveToFile(){

    cout << "Saving to file" << endl;
    ofstream ofile;
    ofile.open("patterns.dat");
    if (ofile.fail())
    {
        cout << "Failed to open the file" << endl;
        return;
    }
    
    for (int i = 0; i < collectionOfMatchBoxes.size(); i++)
    {
        if (collectionOfMatchBoxes[i] != NULL)
        {
            for (int j = 0; j < 9; j++)
            {
                ofile << collectionOfMatchBoxes[i]->getCurrBoard()[j/3][j%3] << ' ';
            }
            for (int j = 0; j < 9; j++)
            {
                ofile << collectionOfMatchBoxes[i]->getPossiableMoves()[j].first << ' ';
                ofile << collectionOfMatchBoxes[i]->getPossiableMoves()[j].second << ' ';
            }
            ofile << endl;
            

            
        }
        
    }
    
    ofile.close();
}

#endif