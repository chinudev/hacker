#include <iostream>
#include <vector> 
#include <assert.h>
#include <algorithm>

using namespace std;

inline bool valid(int row, int col, 
                  int gridSize,
                  vector<vector<int>>& grid) 
{
    if (row < 0 || row >= gridSize || 
        col < 0 || col >= gridSize) {
        return false;
    }
    if (grid[row][col] != 0) return false;
    return true;
}

vector<vector<int>> snakePath(int gridSize,
                              int startRow, int startCol,
                              int windRow,  int windCol)
{
    vector<vector<int>> path(gridSize,vector<int>(gridSize,0));

    int currRow = startRow; 
    int currCol = startCol; 

    for (int count=1 ;count <= gridSize*gridSize; count++) {
        path[currRow][currCol] = count;

        // figure out where the snake goes next
        if (windRow == 0) {
            assert(windCol != 0);
            // try to go with the wind
            if (valid(currRow,currCol+windCol,gridSize,path)) {
                currCol += windCol;
            } else {
                // try to go perpendicular 
                if (valid(currRow+1,currCol,gridSize,path)) {
                    currRow += 1;
                } else if (valid(currRow-1,currCol,gridSize,path)) {
                    currRow -= 1;
                } else {
                    // go against the wind
                    currCol -= windCol;
                }
            }
        } else {
            assert(windCol == 0);
            // try to go with the wind
            if (valid(currRow+windRow,currCol,gridSize,path)) {
                currRow += windRow;
            } else {
                // try to go perpendicular 
                if (valid(currRow,currCol+1,gridSize,path)) {
                    currCol += 1;
                } else if (valid(currRow,currCol-1,gridSize,path)) {
                    currCol -= 1;
                } else {
                    // go against the wind
                    currRow -= windRow;
                }
            }
        }
    }

    return path;
}

void printPath(const vector<vector<int>>& path) 
{
    for (auto row: path) {
        for (auto entry: row) cout << entry << " ";
        cout << endl;
    }
}


void unitTest() 
{
    // wind direction (row,col)
    //  north = -1, 0    : south = +1, 0 
    //  east  =  0,+1    : west =   0,-1 
    auto path1 = snakePath(2, 0,0, 0,1); 
    printPath(path1);
}


int main()
{

    //unitTest();

    int gridSize;
    char direction;
    int startRow, startCol;

    cin >> gridSize >> direction;
    cin >> startRow >> startCol;

    int windRow=0;
    int windCol=0;
    switch (direction) {
        case 'n': windRow = -1; break;
        case 's': windRow = +1; break;
        case 'e': windCol = +1; break;
        case 'w': windCol = -1; break;
    };

    printPath(snakePath(gridSize,startRow,startCol,windRow,windCol));
}

