#include <iostream>
#include <vector> 
#include <assert.h>
#include <algorithm>

using namespace std;

struct VolcanoType
{
public:
    int row; 
    int col;
    int effect;
};


void printGrid(vector<vector<int>>& grid) 
{
    int gridSize = grid.size();
    for (int row=0; row < gridSize; row++) {
        for (int col=0; col < gridSize; col++) {
            printf("%02d  ",grid[row][col]);
        }
        printf("\n");
    }
}

int getMaxEffect(int gridSize, vector<VolcanoType>& volcanoVec)
{
    vector<vector<int>> grid(gridSize,vector<int>(gridSize,0));

    for (auto entry: volcanoVec) {
        grid[entry.row][entry.col] += entry.effect;

        for (int effect=entry.effect-1; effect > 0; effect--) {
            int level = entry.effect-effect;
            int startRow = entry.row - level;
            int endRow   = entry.row + level;
            int startCol = entry.col - level;
            int endCol   = entry.col + level;
            //cout << "adding entries " << effect << ":" << startRow << endRow << startCol << endCol << endl;

            for (int col=max(0,startCol); col <= min(gridSize-1,endCol); col++) {
                if (startRow >= 0)     grid[startRow][col] += effect;
                if (endRow < gridSize) grid[endRow][col]   += effect;
            }
            for (int row=max(0,startRow+1); row <= min(gridSize-1,endRow-1); row++) {
                if (startCol >= 0)     grid[row][startCol] += effect;
                if (endCol < gridSize) grid[row][endCol]   += effect;
            }
            //printGrid(grid);
        }
        //cout << "added entry" << endl;
        //printGrid(grid);
    }

    int maxEffect=-1;
    for (int row=0; row < gridSize; row++) {
        for (int col=0; col < gridSize; col++) {
            maxEffect = max(maxEffect, grid[row][col]);
        }
    }
    return maxEffect;

}


void unitTest() 
{
    vector<VolcanoType> vec1 = { {4,5,6} };
    assert( getMaxEffect(10,vec1) == 6);

    vector<VolcanoType> vec2 = { {3,3,3}, {7,7,4} };
    assert( getMaxEffect(10,vec2) == 4);
}


int main()
{

    unitTest();

    int gridSize, numVolcanoes;
    cin >> gridSize >> numVolcanoes;

    vector<VolcanoType> volcanoVec;

    for (; numVolcanoes > 0; numVolcanoes--) {
        VolcanoType vol;
        // problem description doesn't match example. Going with example
        cin >> vol.row >> vol.col >> vol.effect;
        volcanoVec.push_back(vol);
    }
    cout << getMaxEffect(gridSize, volcanoVec) << endl;

}

