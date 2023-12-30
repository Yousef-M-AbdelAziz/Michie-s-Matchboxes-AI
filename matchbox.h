#ifndef MATCHBOX_H
#define MATCHBOX_H

/**
 * The `matchbox` class represents a possible game state in a tic-tac-toe game. 
 * It contains a 3x3 board and a list of possible moves. Each move is represented as a pair of integers, 
 * where the first integer is the move itself and the second integer is the weight of the move. 
 * The weight is used by the coordinator to make decisions during gameplay.
 * 
 * The class provides methods to get and set the current board and possible moves, 
 * It also provides a constructor that initializes the board to an empty state and the possible moves.
 */

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include <ctime>
#include <unordered_map>

using namespace std;

typedef vector<vector<char>> board;
typedef vector<pair<int, int >> nextMoves;

class matchbox{

    private:
    board currBoard;
    nextMoves possiableMoves;
    




    public:

    board getCurrBoard(){
        return currBoard;
    }

    nextMoves getPossiableMoves(){
        return possiableMoves;
    }

    void setCurrBoard(board currBoard){
        this->currBoard = currBoard;
    }

    void setCurrBoard(int i, int j, char symbol){
        this->currBoard[i][j] = symbol;
    }

    void setPossiableMoves(int i, int first, int second){
        this->possiableMoves[i].first = first;
        this->possiableMoves[i].second = second;
    }

    void setPossiableMoves(nextMoves possiableMoves){
        this->possiableMoves = possiableMoves;
    }

    matchbox(){
        currBoard.resize(3, vector<char>(3));
        possiableMoves.resize(9);

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                currBoard[i][j] = '-';
            }
            
        }

        for (int i = 0; i < 9; i++)
        {
            possiableMoves[i].first = -1;
            possiableMoves[i].second = -1;
        }
        
        

    }

    void print() {
    cout << "Current Board:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << this->currBoard[i][j] << ' ';
        }
        
    }
    

    cout << "Possible Moves:\n";
    for (int i = 0; i < 9; ++i) {
        cout << possiableMoves[i].first << ' ' << possiableMoves[i].second << '\n';
    }
    cout << '\n';
}

    
};


#endif
