// https://www.hackerrank.com/challenges/maximum-subarray-sum

#include <iostream>
#include <vector>
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

// O(n) version 
// This relies on the fact that mod <= 10**14 and n <= 10**5 so total 
//  for whole array will be less than 10**19 that just fits in 
//  uint64
// 
uint64_t findMax(const vector<uint64_t>& numList, uint64_t mod)
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


int main()
{
    cout << findMax1({3,3,9,9,5}, 7) << endl;
    cout << findMax2({3,3,9,9,5}, 7) << endl;
    
    exit(1);
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

        //cout << findMaxSubSum(elemList, mod) << endl;
    }
}
