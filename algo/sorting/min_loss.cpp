// https://www.hackerrank.com/challenges/minimum-loss

#include <vector> 
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <stdint.h>

using namespace std;



uint64_t getMinLoss(vector<pair<uint64_t,int>> priceVector)
{
    // sort in ascending order. Sorting is done with first entry of pair as
    //  primary key viz. price of house. 
    // Pair is used since we want to keep track of the original index so we 
    //  can ensure that house is not sold before it was bought
    sort(priceVector.begin(), priceVector.end());

    uint64_t minLoss = UINT64_MAX;

    // This is O(n^2) but most iteration should exit early
    // Entry (i) corresponds to buy price. Entry (j) corresponds to 
    //  sell price. We only look for lower sell prices

    // Do first quick pass to get a reasonable value of minLoss
    for (int i=1; i < priceVector.size(); i++) {
        //cout << "iterating i " << i << " min loss " << minLoss << endl;
        auto& buyPair = priceVector[i];

        int j=i-1;
        {
            auto& sellPair = priceVector[j];
            uint64_t loss = buyPair.first - sellPair.first;
            // check if index of sellPair was after buyPair in original array
            if (sellPair.second > buyPair.second) {
                if ((loss > 0) && loss < minLoss) {
                    minLoss = loss;
                }
            }
        }
    }

    // Do a full pass to handle any edge cases.
    for (int i=1; i < priceVector.size(); i++) {
        //cout << "iterating i " << i << " min loss " << minLoss << endl;
        auto& buyPair = priceVector[i];

        for (int j=i-1; j >= 0; j--) {
            auto& sellPair = priceVector[j];

            // As we iterate (j) loss becomes greater. Do an 
            //  early exit if loss is already greater than minLoss 
            uint64_t loss = buyPair.first - sellPair.first;
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
    //test();

    int numEntries;
    cin >> numEntries;

    vector<pair<uint64_t,int>> numVector;
    for (int i=0; i < numEntries; i++) {
        uint64_t entry;
        cin >> entry;
        numVector.push_back({entry,i});
    }
    cout << getMinLoss(numVector) << endl;
}
