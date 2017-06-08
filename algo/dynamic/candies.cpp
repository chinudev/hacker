// https://www.hackerrank.com/challenges/candies 

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
#include <math.h>

using namespace std;


uint64_t findNumCandies(vector<int> childRatings) 
{

    if (childRatings.size() == 0) return 0;

    // Add a dummy value to end the last stretch. 
    // This can be done by adding the last element again. This will 
    // cause us to switch to "CONSTANT" state
    childRatings.push_back(childRatings.back());

    /*
    cout << "Testing ";
    for (auto entry : childRatings) cout << entry << " ";
    cout << endl;
    */

    // We track the current state. Either we are staying constant, heading
    // upwards towards a peak or heading downwards to a valley
    // 
    enum StateType {
        INCREASING,
        DECREASING,
        CONSTANT
    };

    uint64_t totalCandies = 0;

    StateType currState = CONSTANT;
    uint64_t currStretchLength = 0;  // This is used in downward or upward strech 
                                     // to figure out how many candies to give to 
                                     // next student.

    uint64_t prevStretchLength = 0;  // This is used to deal with special case of peak
                                     // The peak element's value is dictated by max of 
                                     //  stretch length on either side e.g. consider
                                     //   1,2,4,2  and 1,2,4,3,2,1. 

    for (int i=0; i < childRatings.size()-1; i++) {

        switch (currState) {

            // In constant state student only gets one candy. 
            //  This entry may be start of a upward or downward stretch but 
            //  that the starting element is given one candy
            case CONSTANT: 
                totalCandies += 1;
                currStretchLength = 1;

                if (childRatings[i] == childRatings[i+1]) {
                    // Stay in same state
                } else if (childRatings[i] > childRatings[i+1]) {
                    currState = DECREASING;
                    prevStretchLength = 0;
                } else {
                    currState = INCREASING;
                }
                break;

            // In increasing state student gets candy = length of current stretch
            case INCREASING: 
                currStretchLength++;
                totalCandies += currStretchLength;

                if (childRatings[i] == childRatings[i+1]) {
                    //  Reached a plateau. End of current stretch
                    currState = CONSTANT;

                } else if (childRatings[i] > childRatings[i+1]) {
                    // Heading downward now
                    // we gave currStretchLength candies to this student 
                    // but we may need to give more if downward stretch turns
                    // out to be longer
                    prevStretchLength = currStretchLength;
                    currState = DECREASING;
                    currStretchLength = 0;
                } else {
                    // continue the current stretch
                }
                break;

            // In decreasing state this student would get 1 candy, while incrementing by 
            //  1 candies given to all previous student that are part of this stretch. That 
            //  conveniently works out to be the length of current stretch
            case DECREASING: 
                currStretchLength++;
                totalCandies += currStretchLength;

                // continue downward stretch
                if (childRatings[i] > childRatings[i+1]) break;


                // downward trend ended.
                // check if there was a previous upward stretch that needs
                // to be adjusted
                if (prevStretchLength > 0) {
                    if (currStretchLength >= prevStretchLength) {
                        totalCandies += (currStretchLength - prevStretchLength + 1);
                    }
                    prevStretchLength = 0; 
                }

                if (childRatings[i] == childRatings[i+1]) {
                    //  Reached a plateau. End of current stretch
                    currState = CONSTANT;
                    currStretchLength = 0;

                } else {
                    // Heading upward now
                    currState = INCREASING;
                    currStretchLength = 1;
                }
                break;

        } // end of switch

        /*
        cout << childRatings[i] << " state:" << currState 
             << " total= " << totalCandies 
             << " len = " << currStretchLength 
             << endl;
         */
    }

    return totalCandies;

}

void unitTest()
{
    assert( findNumCandies({2}) == 1);
    assert( findNumCandies({2,2,2}) == 3);
    assert( findNumCandies({2,3,4}) == 6);
    assert( findNumCandies({4,3,2}) == 6);

    assert( findNumCandies({1,2,2}) == 4);
    assert( findNumCandies({2,2,1}) == 4);
    assert( findNumCandies({2,2,3}) == 4);

    assert( findNumCandies({2,2,3,4,4,5,6,6}) == 14);
    assert( findNumCandies({2,4,2,6,1,7,8,9,2,1}) == 19); 
}

int main()
{
    //unitTest();

    int numChildren;
    cin >> numChildren;

    vector<int> childRatings(numChildren,0);
    for (int i=0; i < numChildren; i++) {
        cin >> childRatings[i];
    }

    cout << findNumCandies(childRatings) << endl;

}
