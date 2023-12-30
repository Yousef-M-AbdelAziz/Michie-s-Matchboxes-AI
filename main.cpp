#include<iostream>
#include<vector>
#include<fstream>
#include"matchbox.h"
#include"coordinator.h"

using namespace std;

/**
 * This function is responsible for drawing the current state of the game board.
 * It iterates over each cell in the game board and prints its value.
 * If the cell is empty, it prints a dash. Otherwise, it prints the symbol in the cell.
 * It also prints vertical and horizontal lines to separate the cells.
 */
void drawBoard(const vector<vector<char>>& game) {

    for (int i = 0; i < game.size(); i++) {

            for (int j = 0; j < game[i].size(); j++) {
                if (game[i][j] == '-') {
                    cout << "- ";
                } 
                else {
                    cout << game[i][j] << ' ';
                }
                if (j != game[i].size() - 1) {
                    cout << "| ";
                }
            }

            if (i != game.size() - 1) {
                cout << endl << "---------" << endl;
            }
            
    }
}

/**
 * This function is responsible for making a move in the game.
 * It takes as input the game grid, the position where the move should be made, and the symbol of the player making the move.
 * The function first checks if the position is valid (i.e., between 1 and 9).
 * Then, it calculates the row and column in the grid that correspond to the position.
 * If the cell at the calculated row and column is empty, the function updates the cell with the player's symbol and returns true.
 * If the cell is not empty, the function returns false.
 */
bool makeMove(vector <vector <char>>& grid,int postion, char symbol){
        int r ;
        int c;
       
        if (postion > 9 || postion < 1)
        {
            return false;
        }
        

        if(postion%3 == 0){
            c = 3 -1;
            r = (postion /3) -1 ;
        }
        else{
            c = (postion % 3) - 1;
            r = (postion /3);
        }

        if (grid[r][c] == '-')
        {
          grid[r][c] = symbol;  
        }
        else{
            return false;
        }
        
        return true;

    }

/**
 * This function checks if the game is over.
 * It takes as input the symbol of the player whose turn just ended and the game grid.
 * The function checks all possible winning combinations (rows, columns, and diagonals).
 * If the player has a winning combination, the function returns 1.
 * If there are no empty cells left on the board and no player has a winning combination, the function returns 2, indicating a draw.
 * If neither of these conditions is met, the function returns 0, indicating that the game is not over.
 */
int gameOver(char symbol, vector <vector <char>>& grid){
         int counter =0;
        for (int i = 0; i < 3; i++)
        {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol)
            {
                return 1;
            }
            
        }
           for (int i = 0; i < 3; i++)
        {
            if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)
            {
                return 1;
            }
            
        }

        if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol)
        {
            return 1;
        }
        if(grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol){
            return 1;

        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == '-')
                {
                    counter++;
                }
                
            }
            
        }
        if (counter == 0)
        {
            return 2;
        }
        
        
        
       return 0; 
    }




int main(){




    vector <vector<char>> initialBoard ;
    char choise = 'y';
    coordinator::getMatchBoxes();

    /**
 * This block of code represents the main game loop. It continues as long as the user chooses to play again.
 * The game starts by initializing the game board to an empty state. Then, it enters an inner loop that continues until the game is over.
 * In each iteration of the inner loop, the coordinator makes a move by calling `coordinator::pickMove(initialBoard)`, which chooses the next move based on the current board state. The board is then updated with the coordinator move and displayed.
 * The game checks if the coordinator move resulted in a win. If so, it prints a win message, updates the matchboxes with a win status, and breaks out of the inner loop.
 * If the coordinator move did not result in a win, it's the human player's turn. The player is prompted to enter a move. If the move is invalid, the player is prompted again until a valid move is entered. The board is then updated with the player's move and displayed.
 * The game checks if the player's move resulted in a win. If so, it prints a win message, updates the matchboxes with a loss status, and breaks out of the inner loop.
 * If neither the coordinator nor the player won, the game checks if the game is a draw. If so, it prints a draw message, updates the matchboxes with a draw status, and breaks out of the inner loop.
 * After the game is over, the user is asked if they want to play again. If they choose to play again, the game loop continues. Otherwise, it ends, and the current state of the matchboxes is saved to a file.
 */



    while (choise == 'y')
    {
        initialBoard = {{'-','-','-'},{'-','-','-'},{'-','-','-'}};
        while (true)
        {
            makeMove(initialBoard, coordinator::pickMove(initialBoard), 'x');
            drawBoard(initialBoard);
            cout << endl << endl;

            if (gameOver('x', initialBoard) == true)
            {
                cout << "MatchBoxes wins" << endl;
                coordinator::updateMatchBox(1);
                break;
            }
            else if(gameOver('x', initialBoard) == false)
            {
                int postion;
                cout << "enter postion: ";
                cin >> postion;
                while (makeMove(initialBoard,postion,'o') == false)
                {
                    cout << "Invalid move" << endl;
                    drawBoard(initialBoard);
                    cout << endl;
                    cout << " enter postion: ";
                    cin >> postion;
                }
                drawBoard(initialBoard);
                cout << endl << endl;
                if (gameOver('o', initialBoard) == true)
                {
                    cout << "human wins" << endl;
                    coordinator::updateMatchBox(-1);
                    break;
                }
            }
            else if (gameOver('o', initialBoard) == 2)
            {
                cout << "Draw" << endl;
                coordinator::updateMatchBox(0);
                break;
            }

        }
        
        cout << "Do you want to play again ? (y/n)" << endl;
        cin >> choise;
        coordinator::saveToFile();

    }

    
    

   
    



    return 0;
}