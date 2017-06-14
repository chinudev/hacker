//https://www.hackerrank.com/challenges/angry-children

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

int max_min(int k, vector<int> numVector) 
{
    // start from both ends and keep dropping off the 
    sort(numVector.begin(), numVector.end());

    int leftIndex = 0;
    int rightIndex = numVector.size()-1;

    //cout << "Solving  for " << k << " left:" << leftIndex << " right:" << rightIndex << endl;
    while (rightIndex - leftIndex >= k) {
        int leftDiff = numVector[leftIndex+1] - numVector[leftIndex];
        int rightDiff = numVector[rightIndex] - numVector[rightIndex-1];

        if (leftDiff > rightDiff) {
            leftIndex++;
            //cout << " ** leftIndex " << leftIndex << endl;
        } else { 
            rightIndex--;
            //cout << " ** rightIndex " << rightIndex << endl;
        }
    }
    return numVector[rightIndex] - numVector[leftIndex];
}


void test()
{
    assert(7 == max_min(4,{1,5,6,8}));
    assert(3 == max_min(3,{1,5,6,8}));
    assert(5 == max_min(3,{1,5,6,11}));
    assert(1 == max_min(2,{1,5,6,8}));
    assert(8 == max_min(3,{1,3,100,104,108}));
}

int main()
{
    test();

    int n, k;
    cin >> n >> k;

    vector<int> entryVector(n);
    for (int i=0; i < n; i++) cin >> entryVector[i];
    cout << max_min(k, entryVector) << endl;
}
