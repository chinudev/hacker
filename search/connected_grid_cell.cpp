// https://www.hackerrank.com/challenges/connected-cell-in-a-grid 

#include <iostream>
#include <vector>
#include <stdint.h>
#include <assert.h>

using namespace std; 


int fillSubgrid( vector< vector<int> >& grid, int row, int col) 
{
    if (row >= grid.size()) return 0;
    if (col >= grid[0].size()) return 0;
    if (grid[row][col] == 0) return 0;

    grid[row][col]=0;

    // We don't need to call cells above us or behind us (to left) 
    //  since they would already have been processed 
    return (
            fillSubgrid(grid, row-1, col-1) + 
            fillSubgrid(grid, row-1, col  ) + 
            fillSubgrid(grid, row-1, col+1) + 

            fillSubgrid(grid, row,   col-1) + 
            1 +
            fillSubgrid(grid, row,   col+1) + 

            fillSubgrid(grid, row+1, col-1) + 
            fillSubgrid(grid, row+1, col  ) + 
            fillSubgrid(grid, row+1, col+1) 
            );

}

// This routine will modify the grid
int findMaxSubgrid( vector< vector<int> >& grid) 
{
    int maxGridSize = 0;

    for (int row=0; row < grid.size(); row++) {
        for (int col=0; col < grid[0].size(); col++) {
            if (grid[row][col] == 1) {
                int gridSize = fillSubgrid(grid,row,col);
                if (gridSize > maxGridSize) {
                    maxGridSize = gridSize;
                }
            }
        }
    }
    return maxGridSize;
}

void test1()
{
    vector<vector<int>> grid1 = {{1,0,1},
                                 {0,0,1},
                                 {1,1,0}};
    vector<vector<int>> grid2 = {{0,0,0},
                                 {0,0,0},
                                 {0,0,0}};
    vector<vector<int>> grid3 = {{1,0,1},
                                 {0,0,0},
                                 {1,0,1}};
    vector<vector<int>> grid4 = {{1,1},
                                 {1,1}};

    assert(4 == findMaxSubgrid(grid1));
    assert(0 == findMaxSubgrid(grid2));
    assert(1 == findMaxSubgrid(grid3));
    assert(4 == findMaxSubgrid(grid4));
}


int main()
{

    //test1();

    int numRow, numCol;

    cin >> numRow >> numCol; 
    vector< vector<int> > grid(numRow, vector<int>(numCol,0));

    for (int row=0; row < numRow; row++) {
        for (int col=0; col < numCol; col++) {
            cin >> grid[row][col];
        }
    }

    cout << findMaxSubgrid(grid) << endl;
}
