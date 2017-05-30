//https://www.hackerrank.com/challenges/board-cutting
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;


int findCost(vector<int> columnCost, vector<int> rowCost) 
{
    sort(columnCost.begin(), columnCost.end());
    sort(rowCost.begin(), rowCost.end());

    int currCol=columnCost.size()-1;
    int currRow=rowCost.size()-1;
    int colFragments=1;
    int rowFragments=1;
    int totalCost=0;
    static const int mod = 10*1000*1000*1000 + 7;

    while ((currCol >= 0) || (currRow >= 0)) {
        bool columnCut=true;

        if (currCol < 0) {
            assert(currRow >= 0);
            columnCut = false;
        } else if (currRow < 0) {
            assert(currCol >= 0);
            columnCut = true;
        } else if (columnCost[currCol] < rowCost[currRow]) {
            columnCut = false;
        } else {
            columnCut=true;
        }

        if (columnCut) {
            totalCost = (totalCost + columnCost[currCol]*rowFragments) % mod;
            colFragments++;
            currCol--;
        } else {
            totalCost = (totalCost + rowCost[currRow]*colFragments) % mod;
            rowFragments++;
            currRow--;
        }
    }
    return totalCost;
}

void test()
{
    assert(findCost({2}, {1}) == 4);
    assert(findCost({2,1,3,1,4}, {4,1,2}) == 42);
}

int main()
{
    //test();

    int numQuery;
    cin >> numQuery;
    for (;numQuery > 0; numQuery--) {
        int numRow, numCol, entry;
        cin >> numRow >> numCol;

        vector<int> rowCost;
        for (;numRow > 1; numRow--) {
            cin >> entry;
            rowCost.push_back(entry);
        }

        vector<int> colCost;
        for (;numCol > 1; numCol--) {
            cin >> entry;
            colCost.push_back(entry);
        }
        cout << findCost(rowCost, colCost) << endl;
    }
}
