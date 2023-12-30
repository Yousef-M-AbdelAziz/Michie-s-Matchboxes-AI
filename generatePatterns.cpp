#include<iostream>
#include <vector>
#include<fstream>

using namespace std;


bool checkPattern(vector <char>& pattern){
    int xnum = 0;
    int onum = 0;

    for (int i = 0; i < pattern.size(); i++)
    {
        if (pattern[i] == 'x')
        {
            xnum++;
        }
        else if (pattern[i] == 'o')
        {
            onum++;
        }
        
    }

    if(xnum - onum > 1 || onum - xnum > 1){
        return false;
    }
    else
    {
        return true;
    }


    
}

bool gameOver(vector<char>& pattern) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (pattern[i] != ' ' && pattern[i] == pattern[i + 1] && pattern[i] == pattern[i + 2] && pattern[i] != '-') {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (pattern[i] != ' ' && pattern[i] == pattern[i + 3] && pattern[i] == pattern[i + 6] && pattern[i] != '-') {
            return true;
        }
    }

    // Check diagonals
    if (pattern[0] != ' ' && pattern[0] == pattern[4] && pattern[0] == pattern[8] && pattern[0] != '-') {
        return true;
    }
    if (pattern[2] != ' ' && pattern[2] == pattern[4] && pattern[2] == pattern[6] && pattern[2] != '-') {
        return true;
    }

    // No win
    return false;
}

void generatePatterns(vector <char>& pattern, int currentChar, char characters[], int currentCell, ofstream& fout){
    if (currentCell > 8)    
    {
        if (checkPattern(pattern) == true && gameOver(pattern) == false)
        {
            for (int i = 0; i < pattern.size(); i++)
            {
                fout << pattern[i] << " ";
            }

            
            for (int i = 0; i < 9; i++)
            {
                if(pattern[i] != '-'){
                    fout << i + 1 << " " << 0 << " ";
                }
                else{
                    fout << i+1 << " " << 2 << " ";
                }
            }
            
            fout << endl;
            
         
        }
        
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            pattern[currentCell] = characters[i];
            generatePatterns(pattern, i, characters, currentCell + 1, fout);
        }
        
    }

    
}



int main(){
    char characters[3] = {'-', 'x', 'o'};
    int current = 0;
    vector <char> pattern;
    pattern.resize(9);
    ofstream fout;

    fout.open("patterns.dat");

    if (fout.fail())
    {
        cout << "File isuue" << endl;

    }
    else{
        generatePatterns(pattern, current, characters, 0, fout);

    }
    


    

   
    









    return 0;
}