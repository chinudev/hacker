// https://www.hackerrank.com/challenges/stockmax/problem

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
#include <math.h>

using namespace std;

uint64_t getProfit(vector<int> priceVector) 
{
    int n = priceVector.size();

    // pair.first = share price, pair.second = index
    // we want to sort in decreasing price, with secondary key as 
    //  increasing index. so we will store price as -ve
    vector<pair<int,int>> sortedPrice;
    for (int i=0; i < n; i++) {
        sortedPrice.push_back(make_pair(-priceVector[i], i));
    }
    sort(sortedPrice.begin(),sortedPrice.end());

    int currIndex = 0;
    uint64_t totalProfit = 0;
    for (auto elem: sortedPrice) {
        int price = -elem.first;
        int index = elem.second;

        // if index <= currIndex, it has already been processed
        if (currIndex < index) {
            for (;currIndex < index; currIndex++) {
                int delta = price - priceVector[currIndex];
                if (delta > 0) totalProfit += delta;
            }
            currIndex++;  // this incr is for the sell date
        }
    }
    return totalProfit;
}

void unitTest() 
{
    assert(0 == getProfit({5,3,2}));
    assert(197 == getProfit({1,2,100}));
    assert(3 == getProfit({1,3,1,2}));
    assert(0 == getProfit({1}));
    cout <<  getProfit({1,2,3,4}) << endl;;
    cout <<  getProfit({1,2,3,2,1}) << endl;;
    exit(0);
}

int main()
{
    //unitTest();

    int numTest;
    cin >> numTest;

    for (int i=0; i < numTest; i++) {
        int numEntries;
        cin >> numEntries;
        vector<int> priceVector(numEntries);
        for (int j=0; j < numEntries; j++) {
            cin >> priceVector[j];
        }
        cout << getProfit(priceVector) << endl;
    }

}
