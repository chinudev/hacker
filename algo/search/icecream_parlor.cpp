// https://www.hackerrank.com/challenges/icecream-parlor

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <assert.h>

using namespace std; 


pair<int, int> findPair(vector<int> numVector, int sum) 
{
    vector<pair<int,int>> pairVector;
    for (auto i=0; i < numVector.size(); i++) {
        pairVector.push_back(make_pair(numVector[i], i+1));
    }
    sort(pairVector.begin(),pairVector.end());

    int leftIndex = 0;
    int rightIndex = pairVector.size()-1;

    while (leftIndex < rightIndex) {
        auto leftPair =pairVector[leftIndex];
        auto rightPair =pairVector[rightIndex];

        int currSum = leftPair.first + rightPair.first; 
        if (currSum == sum) {
            if (leftPair.second > rightPair.second) {
                return(make_pair(rightPair.second, leftPair.second));
            } 
            return(make_pair(leftPair.second, rightPair.second));
        }

        if (currSum > sum) rightIndex--;
        if (currSum < sum) leftIndex++;
    }

    // We will exit the loop only if no solution was found
    // Per problem statement there will be at least one solution
    assert(false);  

    return pair<int,int>(-1,-1);
}


void unitTest()
{
    assert(make_pair(1,4) == findPair({1,4,5,3,2},4) );
    assert(make_pair(1,2) == findPair({2,2,4,3},4));
}


int main()
{
    //unitTest();
    int numTest;
    cin >> numTest;
    for (; numTest > 0; numTest--) {
        int sum;
        int numEntries;
        cin >> sum >> numEntries;

        vector<int> numVector(numEntries,0);
        for (int i=0; i < numEntries; i++) {
            cin >> numVector[i];
        }

        auto answer = findPair(numVector, sum);
        cout << answer.first << " " << answer.second << endl;
    }

}
