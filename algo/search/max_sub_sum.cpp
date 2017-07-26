// https://www.hackerrank.com/challenges/maximum-subarray-sum

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stdint.h>

using namespace std; 

// First implementation. Overly complicated O(n^2) version :-) 
uint64_t findMax1(const vector<uint64_t>& numList, uint64_t mod)
{
    vector<uint64_t> sumList(numList.size(),0);
    uint64_t maxSum=0;

    for (int i=0; i<numList.size(); i++) {
        // We are considering sub-arrays of length (i+1)
        // These sub-arrays start from index 0
        for (int k=i; k<numList.size(); k++) {
            sumList[k-i] = (sumList[k-i] + numList[k]) % mod;
            if (sumList[k-i] > maxSum) {
                maxSum=sumList[k-i];
            }
        }
    }
    return maxSum;
}

// Second implementation for reference only. 
// Simpler version of O(n^2)
uint64_t findMax2(const vector<uint64_t>& numList, uint64_t mod)
{
    uint64_t maxSum=0;

    for (int start=0; start<numList.size(); start++) {
        uint64_t subSum=0;
        for (int end=start; end<numList.size(); end++) {
            subSum = (subSum + numList[end]) % mod;
            if (subSum > maxSum) {
                maxSum = subSum;
            }
        }
    }
    return maxSum;
}

// 
uint64_t findMax(const vector<uint64_t>& numList, uint64_t mod)
{

    // This stores partial sums in sorted order. 
    //  Pair contains first=sum, second=index
    vector<uint64_t> partialSumVec(numList.size());

    uint64_t maxSum=0;
    uint64_t currSum=0;
    for (int i=0; i < numList.size(); i++)  {
        auto elem = numList[i];
        currSum = (currSum + elem) % mod;
        partialSumVec[i] = currSum;
        maxSum = max(maxSum, currSum);
        maxSum = max(maxSum, elem);
    }

    //cout << "partial sum vector = ";
    //for (auto elem: partialSumVec) cout << elem << ",";
    //cout << endl;

    // This set contains partialSum for all elements processed till now. 
    //  Starts off as empty 
    set<uint64_t> partialSumSet;
    for (auto partialSum: partialSumVec) {
        //maxSum = max(maxSum, partialSum);

        // look for the smallest "partial sum" greater than this element in set
        auto it = partialSumSet.upper_bound(partialSum);
        if (it != partialSumSet.end()) {
            uint64_t temp = (partialSum - *it + mod) % mod;
            maxSum = max(maxSum, temp);
            //cout << partialSum << "**=>" << maxSum << endl;
        }
        partialSumSet.insert(partialSum);
        //cout << partialSum << "=>" << maxSum << endl;
    }

    return maxSum;
}


int main()
{
    //cout << findMax2({3,3,9,9,5}, 7) << endl;
    //cout << findMax({3,3,9,9,5}, 7) << endl;
    
    int numQuery;

    cin >> numQuery; 
    for (; numQuery>0; numQuery--) {
        int numElems;
        uint64_t mod;

        cin >> numElems >> mod;
        vector<uint64_t> elemList;

        for (; numElems>0; numElems--) {
            uint64_t elem;
            cin >> elem;
            elemList.push_back( elem % mod);
        }

        cout << findMax(elemList, mod) << endl;
    }
}
