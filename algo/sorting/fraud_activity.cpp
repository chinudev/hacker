// https://www.hackerrank.com/challenges/fraudulent-activity-notifications

#include <vector> 
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;


double computeMedian(vector<int> numInstances, int count) 
{
    int midIndex = int((count+1)/2);
    int midValue = 0;
    int midPlus1Index = midIndex + 1;
    int midPlus1Value = 0;

    int index = 0;
    for (int i = 0; i < numInstances.size(); i++) {
        index += numInstances[i];
        if ((index >= midIndex) && (midValue == 0)) {
            midValue = i;
        }
        if ((index >= midPlus1Index) && (midPlus1Value == 0)) {
            midPlus1Value = i;
            break;
        }
    }

    if (count % 2 == 1) return midValue;

    return (double(midValue + midPlus1Value)/2);
}

int getNotifications(vector<int> numVector, int numDays) 
{
    vector<int> numCount(201,0);

    int index=0;
    for ( ;index < numDays; index++) numCount[numVector[index]]++;

    int numNotifications=0;

    for ( ; index < numVector.size(); index++) {
        int newValue = numVector[index];
        double median = computeMedian(numCount, numDays);
        if (double(newValue) >= 2*median) numNotifications++;

        // Prepare for next iteration
        int oldValue = numVector[index-numDays];
        numCount[newValue]++;
        numCount[oldValue]--;
    }

    return numNotifications;
}



void test() 
{
    vector<int> numCount = {0,2,1,2};
    assert( computeMedian(numCount, 5) == 2); 
    assert( computeMedian(numCount, 4) == 1.5); 

    assert(2 == getNotifications({2,3,4,2,3,6,8,4,5}, 5));
    assert(3 == getNotifications({1,2,4,7,15}, 1));
    assert(4 == getNotifications({2,2,4,6,11,17,27}, 2));
    assert(2 == getNotifications({1,2,3,4,5,9}, 3));
    assert(0 == getNotifications({1,2,3,4,4}, 4));
}

int main() 
{
    //test();

    int numEntries, numDays;
    cin >> numEntries >> numDays;

    vector<int> numVector;
    for (; numEntries > 0; numEntries--) {
        int entry;
        cin >> entry;
        numVector.push_back(entry);
    }
    cout << getNotifications(numVector, numDays) << endl;
}
