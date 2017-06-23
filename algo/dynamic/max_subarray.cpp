//https://www.hackerrank.com/challenges/maxsubarray

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

using namespace std;



pair<int64_t,int64_t> maxSubSum(vector<int>& numVector) 
{

    int maxVal = INT_MIN;
    int maxSum = 0;
    for (int elem: numVector) {
        maxVal = max(maxVal,elem);
        if (elem > 0) maxSum += elem;
    }
    if (maxVal <= 0) {
        // if all values are -ve, maxVal is answer for both 
        return make_pair(maxVal, maxVal);
    } 

    int64_t maxSubSum = 0;
    int64_t currSubSum = 0;
    for (int elem: numVector) {
        if (currSubSum < 0) currSubSum = elem;
        else  currSubSum += elem;
        maxSubSum = max(maxSubSum, currSubSum);
    }

    return make_pair(maxSum, maxSubSum);

}

// easier to use for testing
bool MaxSubSum(vector<int> numVector, int64_t t1, int64_t t2) 
{
    auto ans = maxSubSum(numVector);
    //cout << " ans = " << t1 << " " << t2 << endl;
    //cout << " ans = " << ans.first << " " << ans.second << endl;
    return (ans == make_pair(t1,t2));
}


void unitTest()
{
    assert( MaxSubSum({-21,-2,-3,-4} , -2, -2));
    assert( MaxSubSum({0,0,0,0} , 0, 0));
    assert( MaxSubSum({1,2,3,4} , 10, 10));
    assert( MaxSubSum({2,-1,2,3,4,-5} , 11, 10));
}

int main()
{
    //unitTest();

    int numQuery;
    cin >> numQuery;


    for (int q=0; q < numQuery; q++) {
        int numEntry;
        cin >> numEntry;
        vector<int> numVector(numEntry);
        for (int i=0; i < numEntry; i++) cin >> numVector[i];

        auto ans = maxSubSum(numVector);
        cout << ans.second << " " << ans.first << endl;
    }

}
