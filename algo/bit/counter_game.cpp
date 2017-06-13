// https://www.hackerrank.com/challenges/counter-game
#include <iostream>
#include <bitset>
#include <assert.h>
#include <stdint.h>

using namespace std;


int getNumTurns(uint64_t num)
{


    // find bit position for 1 at LSB
    int bitPos = 0;
    while (num % 2 == 0) {
        num = num >> 1;
        bitPos++;
    }
    num = num >> 1;

    // find number of 1s remaining in num
    int numOnes = 0;
    while (num != 0) {
        if (num % 2 == 1) numOnes++;
        num = num >> 1;
    }


    return numOnes + bitPos;
}



void test()
{
    assert(0 == getNumTurns(1));
    assert(1 == getNumTurns(2));
    assert(4 == getNumTurns(16));
    assert(1 == getNumTurns(3));
    assert(2 == getNumTurns(6));
    assert(2 == getNumTurns(21));
}


int main()
{
    test();
    int numTest;
    cin >> numTest;

    for (;numTest > 0; numTest--) {
        uint64_t num;
        cin >> num;
        int numTurns = getNumTurns(num);
        if (numTurns % 2 == 0) {
            cout << "Richard" << endl;
        } else  {
            cout << "Louise" << endl;
        }

    }

}
