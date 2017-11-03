#include <iostream>
#include <vector> 
#include <utility>
#include <assert.h>
#include <algorithm>
#include <stdint.h>
#include <string>

using namespace std;

void printGrid(vector<vector<bool>>& freeGrid) 
{
    for (auto& freeRow : freeGrid) {
        for (bool cell : freeRow) {
            if (cell) cout << ".";
            else cout << "X";
        }
        cout << endl;
    }
}

uint32_t findWins(vector<vector<bool>>& freeGrid, 
                  pair<int,int> king1, 
                  pair<int,int> king2)
{
    uint32_t numWins=0;
    printGrid(freeGrid);
    cout << "Rowsize = " << freeGrid.size() << " ColSize = " << freeGrid[0].size() << endl;
    cout << "King1 @ " << king1.first << " " << king1.second << endl;
    cout << "King2 @ " << king2.first << " " << king2.second << endl;
    return 0;
}

int main()
{

    //unitTest();

    int numTest;
    cin >> numTest;

    for (;numTest > 0;numTest--) {
        int gridSize;
        cin >> gridSize;

        // track if a cell has obstacle or free
        vector<vector<bool>> freeGrid(gridSize, vector<bool>(gridSize,true));
        pair<int,int> king1, king2;  // store row,col
        bool king1Found=false;

        for (int row=0; row < gridSize; row++) {
            vector<bool>& freeRow = freeGrid[row];
            string strRow;
            cin >> strRow;
            for (int col=0; col < strRow.size(); col++) {
                if (strRow[col] == 'X') {
                    freeRow[col] = false;
                } else if (strRow[col] == 'K') {
                    if (king1Found) {
                        cout << "added king2 @ " << row << "," << col << endl;
                        king2.first = row;
                        king2.second = col;
                    } else {
                        cout << "added king1 @ " << row << "," << col << endl;
                        king1.first = row;
                        king1.second = col;
                        king1Found = true;
                    }
                }
            }
            cout << " free grid size = " << freeGrid.size() << "," << freeGrid[row].size() << endl;
        }
        uint32_t numWins = findWins(freeGrid, king1, king2);
        if (numWins == 0) {
            cout << "LOSE" << endl;
        } else {
            cout << "WIN " << numWins << endl;
        }
    }
}

