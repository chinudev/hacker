// https://www.hackerrank.com/challenges/maximum-subarray-sum

#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std; 

uint64_t findMaxSubSum(const vector<uint64_t>& numList, uint64_t mod)
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


int main()
{
    //cout << findMaxSubSum({3,3,9,9,5}, 7) << endl;
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

        cout << findMaxSubSum(elemList, mod) << endl;
    }
}
