// https://www.hackerrank.com/challenges/xor-se
#include <iostream>
#include <bitset>
#include <assert.h>

using namespace std;
typedef unsigned long long uint64;

/*
 * A[i] = A[i-1] ^ i
 * B[i] = B[i-1] ^ A[i]
 *
 * Compute using brute-force and notice the pattern in first few values 
 * of B[..] 
*/
uint64 computeB(uint64 n)
{
    uint64 B;

    // Handle bit0 and bit1 as special cases. 
    // Bit0 follows the pattern 0,1,0,0. 
    uint64 bit0[4] = {0,1,0,0};
    // Bit1 follows the pattern 0,0,1,1,1,1,0,0
    uint64 bit1[8] = {0,0,2,2,2,2,0,0};

    B = bit0[n%4] | bit1[n%8];

    // Bit k (2..) follow this pattern
    //   2**k 0, followed by 2**(k-2) reps of [1,1,0,0]


    uint64 bitKTemplate[4] = {1,1,0,0};

    uint64 powK=4;    // start from bit 2
                      // alternative would be to use 1<<k

    while (powK <= n) {      
        // overall pattern repeats every 2**(k+1) numbers
        uint64 patternIndex = n % (powK*2);

        // if patternIndex < powK we get a 0. That doesn't require 
        //   any operation
        if (patternIndex >= powK) {
            uint64 value = bitKTemplate[ patternIndex % 4] * powK;
            B = B | value;
        }
        powK = powK*2;
    }
    return B;
}

uint64 bruteB(uint64 n)
{
    uint64 A=0;
    uint64 B=0;
    for (uint64 i=0; i<=n; i++) {
        A = A^i;
        B = B^A;
    }
    return B;
}

void testCompute() 
{
    for (int i=0; i<128; i++) {
        if (bruteB(i) == computeB(i)) {
            cout << i << " = " 
                 << std::bitset<8>(computeB(i))  << " = " 
                 << std::bitset<8>(bruteB(i)) << endl;
        } else {
            cout << i << " = " 
                 << std::bitset<8>(computeB(i))  << " ! " 
                 << std::bitset<8>(bruteB(i)) << endl;
        }
        assert(bruteB(i) == computeB(i));
    }

}
void test2()
{
    cout << "2 4 = " << (computeB(1) ^ computeB(4)) << endl;
    cout << "2 8 = " << (computeB(1) ^ computeB(8)) << endl;
    cout << "5 9 = " << (computeB(4) ^ computeB(9)) << endl;
}


/*
 * A[i] = A[i-1] ^ i
 * B[i] = B[i-1] ^ A[i]
 *
 * You should be able to see that answer we are looking for can be
 * expressed as B. 
 * xor_seq(A[l]..A[r]) =  B[l-1] ^ B[r]
 *
*/
int main()
{
    testCompute();
    test2();

}
