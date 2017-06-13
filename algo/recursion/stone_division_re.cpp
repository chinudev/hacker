// https://www.hackerrank.com/challenges/stone-division-2

#include <iostream>
#include <vector> 
#include <algorithm>
#include <assert.h>
#include <stdint.h>

using namespace std;

int getNumMoves(uint64_t n, vector<uint64_t> numSet)
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

    numMoves[0].first = 1;  // Only one move possible for smallest number

    for (int i=0; i < numMoves.size(); i++) {
        uint64_t currMoves  = numMoves[i].first;
        uint64_t currNumber = numMoves[i].second;

        for (int j=i+1; j < numMoves.size(); j++) {
            // If this number (at index j)  is divisible by currNumber, then 
            //   currNumber is a possible next move. Check to see if using 
            //   currNumber would lead to a better move
            if (numSet[j] % currNumber == 0) {
                if (numMoves[j].first <= currMoves) {
                    numMoves[j].first = currMoves + 1;
                }
            }
        }
    }

    // Sort in descending order (note rbegin instead of begin)
    sort(numMoves.rbegin(), numMoves.rend());

    // figure out num moves for "n"
    // 
    uint64_t moves = 0;
    uint64_t pileSize  = n;
    uint64_t pileCount = 1;

    //cout << "Finding moves for " << n << endl;
    //cout << " found match pileSize,pileCount,moves  first,second" << endl;

    bool keepLooping = true;
    while (keepLooping) {
        keepLooping = false;
        for (auto entry : numMoves) {
            if ((pileSize != entry.second) && (pileSize % entry.second == 0)) {
                //cout << " found match " << pileSize << "," << pileCount << "," << moves << "   " << entry.first << "," << entry.second << endl;
                moves += pileCount;
                pileCount = pileCount * uint64_t(pileSize / entry.second);
                pileSize = entry.second;
                keepLooping = true;
                break;
            }
        }
    }

    return moves;
}


void test()
{
    assert(4 == getNumMoves(12, {4,3,2}));
    assert(1 == getNumMoves(12, {2}));
    assert(0 == getNumMoves(12, {5}));
    assert(39 == getNumMoves(96, {48,6,8,2,3,4}));
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
        cout << getNumMoves(n, numSet);
    }
}
