// https://www.hackerrank.com/contests/w33/challenges/palindromic-table

#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

struct AnswerType {
    int area;
    int topRow;
    int leftCol;
    int bottomRow;
    int rightCol;

    int operator==(const AnswerType& right) const {
        return (topRow == right.topRow) &&
               (leftCol == right.leftCol) &&
               (bottomRow == right.bottomRow) &&
               (rightCol == right.rightCol);
    }

    void print() {
        cout << area << " (" << topRow << "," << leftCol << ") (" 
             << bottomRow << "," << rightCol << ")" << endl;
    }
    void printOut() {
        cout << area << endl;
        cout << topRow << " " << leftCol << " " 
             << bottomRow << " " << rightCol << endl;
    }
};

bool isPalindrome(vector<int> digitCount)
{
    int numOdds=0;
    int total=0;
    for (int c: digitCount) {
        total += c;
        if (c % 2 == 1) numOdds++;
    }
    if (total == 1) return true;    // handle case of single 0
    if (numOdds > 1) return false; 
    if (total - digitCount[0] < 2) return false;
    return true;
}


// Brute force approach
AnswerType getLargest(vector<vector<int>>& grid)
{
    AnswerType answer = {0,0,0,0,0};
    int maxRows = grid.size();
    int maxCols = grid[0].size();

    // A rectangle sub-grid can start at any row,col. 
    //  For each sub-grid track the digit-count in an array [0..10]
    vector<vector<vector<int>>> subGrid(maxRows,vector<vector<int>>
                                                 (maxCols, vector<int>(10,0)));

    // "rows" and "cols" track size of the current beautiful rectangle we 
    //   are looking for. 

    int maxArea = 0; 

    for (int rows=maxRows; rows > 0; rows--) {
        if (rows*maxCols < maxArea) break;

        for (int cols=maxCols; cols > 0; cols--) {
            if (rows*cols < maxArea) break;

            for (int row=0; row <= maxRows-rows; row++) {
                if (rows*cols <= maxArea) break;

                for (int col=0; col <= maxCols-cols; col++) {
                    vector<int> digitCount(10,0);
                    for (int i=0; i < rows; i++) {
                        for (int j=0; j < cols; j++) {
                            digitCount[ grid[row+i][col+j] ] ++;
                        }
                    }

                    //cout << "checking " << row << " " << col << " : " << rows << " X " << cols << endl;
                    if (isPalindrome(digitCount)) {
                        maxArea = rows*cols;
                        answer.area = maxArea; 
                        answer.topRow = row; 
                        answer.bottomRow = row+rows-1;
                        answer.leftCol = col; 
                        answer.rightCol = col+cols-1;
                        break;
                    }
                }
            }
        }
    }
    //cout << "returning "; answer.print();

    return answer;
}


bool checkGetLargest(AnswerType expected, vector<vector<int>> grid)
{
    return (expected == getLargest(grid));
}

void test()
{
    assert(false == isPalindrome({0,1,2,3,4,5,6,7,8,9}));
    assert(true  == isPalindrome({1,0,0,0,0,0,0,0,0,0}));
    assert(false == isPalindrome({2,0,0,0,0,0,0,0,0,0}));
    assert(true  == isPalindrome({0,1,0,0,0,0,0,0,0,0}));
    assert(true  == isPalindrome({0,2,0,0,0,0,0,0,0,0}));
    assert(true  == isPalindrome({0,3,0,0,0,0,0,0,0,0}));
    assert(true  == isPalindrome({1,2,0,0,0,0,0,0,0,0}));
    assert(true  == isPalindrome({2,2,0,0,0,0,0,0,0,0}));
    assert(true  == isPalindrome({2,3,0,0,0,0,0,0,0,0}));
    assert(false == isPalindrome({1,3,0,0,0,0,0,0,0,0}));

    cout << "isPalindrome test passed " << endl;

    assert(checkGetLargest({4,0,0,1,1} , {{1,1},{1,1}}));
    assert(checkGetLargest({9,0,0,2,2} , {{1,1,1},{1,0,1},{1,1,1}}));
    assert(checkGetLargest({8,0,0,1,3} , {{1,2,0,3,2},{0,1,2,3,4},{0,9,8,9,0}}));

    cout << "getLargest test passed " << endl;
}

int main() 
{

    //test();
    int rows, cols;
    cin >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols,0));

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            cin >> grid[i][j];
        }
    }

    AnswerType ans = getLargest(grid);
    ans.printOut();
}

