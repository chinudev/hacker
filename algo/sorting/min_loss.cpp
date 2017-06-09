// https://www.hackerrank.com/challenges/minimum-loss

#include <vector> 
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;



int getMinLoss(vector<pair<int,int>> priceVector)
{
    // sort in ascending order. Sorting is done with first entry of pair as
    //  primary key viz. price of house. 
    // Pair is used since we want to keep track of the original index so we 
    //  can ensure that house is not sold before it was bought
    sort(priceVector.begin(), priceVector.end());

    //for (auto entry : priceVector) cout << entry.first << " " << entry.second << endl;

    int minLoss = 1 << 30;

    // This is O(n^2) but most iteration should exit early
    // Entry (i) corresponds to buy price. Entry (j) corresponds to 
    //  sell price. We only look for lower sell prices

    //for (int i=1; i < priceVector.size(); i++) 
    for (int i=priceVector.size()-1; i > 0; i--) {
        auto& buyPair = priceVector[i];

        for (int j=i-1; j >= 0; j--) {
            auto& sellPair = priceVector[j];

            // As we iterate (j) loss becomes greater. Do an 
            //  early exit if loss is already greater than minLoss 
            int loss = buyPair.first - sellPair.first;
            if (loss > minLoss) break;
            if (loss == 0) continue;           // loss of 0 not allowed

            // check if index of sellPair was after buyPair in original array
            if (sellPair.second > buyPair.second) {
                minLoss = loss;
                break;
            }
        }
    }

    return minLoss;

}


void test() 
{
    assert(2 == getMinLoss({{5,0},{10,1},{3,2}}));
    assert(2 == getMinLoss({{20,0},{7,1},{8,2},{2,3},{5,4}}));
}

int main() 
{
    test();

    int numEntries;
    cin >> numEntries;

    vector<pair<int,int>> numVector;
    for (int i=0; i < numEntries; i++) {
        int entry;
        cin >> entry;
        numVector.push_back({entry,i});
    }
    cout << getMinLoss(numVector) << endl;
}
