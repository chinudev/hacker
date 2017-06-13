// https://www.hackerrank.com/challenges/stone-division-2

#include <iostream>
#include <vector> 
#include <algorithm>
#include <assert.h>
#include <stdint.h>

using namespace std;

uint64_t getNumMoves(uint64_t n, vector<uint64_t> numSet)
{
    sort(numSet.begin(), numSet.end());

    // We will compute number of moves that can be generated  for each entry
    //   in numSet.
    // We will store a pair to track each entry : 
    //    first = numMoves 
    //    second = value viz. numSet[i] 
    // Initially this vector is in increasing order of value. Later 
    //   we will sort this by numMoves

    vector< pair<uint64_t, uint64_t>> numMoves(numSet.size());
    for (int i=0; i < numSet.size(); i++) {
        numMoves[i].first = 0;
        numMoves[i].second = numSet[i];
    }

    for (int i=0; i < numMoves.size(); i++) {
        uint64_t currMoves  = numMoves[i].first;
        uint64_t currNumber = numMoves[i].second;

        for (int j=i+1; j < numMoves.size(); j++) {
            // If this number (at index j)  is divisible by currNumber, then 
            //   currNumber is a possible next move. Check to see if using 
            //   currNumber would lead to a better move
            if (numSet[j] % currNumber == 0) {

                // Possible moves  = 1 : Divide (numSet[j]) into number/currNumber piles 
                //                  + numPiles * currMoves  : divide each pile 
                uint64_t possMoves = uint64_t(numSet[j] / currNumber)* currMoves + 1;
                if (numMoves[j].first < possMoves) {
                    numMoves[j].first = possMoves;
                }
            }
        }
    }

    //for (auto entry : numMoves)  cout << " (" << entry.first <<"," << entry.second << ") ";
    //cout << endl;

    uint64_t maxMoves = 0;
    for (pair<uint64_t,uint64_t> entry : numMoves) {
        if ((n != entry.second) && (n % entry.second == 0)) {
            uint64_t possMoves = uint64_t(n/entry.second)*entry.first + 1;
            //cout << " iterate :" << entry.second << " = " << maxMoves << " " << possMoves << endl;
            maxMoves = max(maxMoves, possMoves);
        }
    }
    return maxMoves;
}


void test()
{
    assert(4 == getNumMoves(12, {4,3,2}));
    assert(1 == getNumMoves(12, {2}));
    assert(0 == getNumMoves(12, {5}));
    assert(39 == getNumMoves(96, {48,6,8,2,3,4}));

    assert(1112738372 == getNumMoves(99033715019, {1,99033715019,89,1112738371,864721694069}));
}


int main()
{
    //test();

    int numTest;
    cin >> numTest; 
    for (; numTest > 0; numTest--) {
        uint64_t n, setSize;
        cin >> n >> setSize;
        vector <uint64_t> numSet(setSize);

        for (auto i=0; i < setSize; i++) {
            cin >> numSet[i];
        }
        cout << getNumMoves(n, numSet) << endl;
    }
}
