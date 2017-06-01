//https://www.hackerrank.com/challenges/sherlock-and-cost

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

using namespace std;

// We want to maximize peaks and valleys so we should each Ai to min (1) or 
//   max (Bi). To prove this imagine a sub-segment of 3 points where middle 
//   point is between 1 and Bi. We can show that it never reduces the cost 
//   to move middle to min or max but sometimes it can improve the cost.
// For a two element array : we compare right

int getMaxCost(vector<int> elemVector)
{
    uint64_t costWhenPrevElementMin = 0;
    uint64_t costWhenPrevElementMax = 0;
    int prevElementMaxValue =  elemVector[0];

    for (int i=1; i < elemVector.size(); i++) {
        // Consider the current element is 1 or max (Bi)
        
        // assume current element=1, and compute cost for prev element being
        //   min or max 
        uint64_t costMin1 = costWhenPrevElementMin + (1-1);
        uint64_t costMin2 = costWhenPrevElementMax + abs(1 - prevElementMaxValue);

        // assume current element=Ai, and compute cost for prev element being
        //   min or max 
        uint64_t costMax1 = costWhenPrevElementMin + abs(elemVector[i] - 1);
        uint64_t costMax2 = costWhenPrevElementMax + abs(elemVector[i] - prevElementMaxValue);

        // Update for next round
        costWhenPrevElementMin = max(costMin1, costMin2);
        costWhenPrevElementMax = max(costMax1, costMax2);
        prevElementMaxValue = elemVector[i];

        /*
        cout << costMin1 << " " << costMin2 << " "; 
        cout << costMax1 << " " << costMax2 << " "; 
        cout << costWhenPrevElementMin << " "; 
        cout << costWhenPrevElementMax << " "; 
        cout << prevElementMaxValue << endl; 
        */
    }
    return max(costWhenPrevElementMin, costWhenPrevElementMax); 
}


void test()
{
    assert(36 == getMaxCost({10,1,10,1,10}));
    assert(396 == getMaxCost({10,100,10,100,10}));
}

int main()
{
    test();
    
    int numTest;
    cin >> numTest;
    for (; numTest > 0; numTest--) {
        int numElem;
        cin >> numElem;

        vector<int> B(numElem);
        for (int i=0; i < numElem; i++)  cin >> B[i];

        cout << getMaxCost(B) << endl;
    }
    
}
