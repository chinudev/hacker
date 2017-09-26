//https://www.hackerrank.com/challenges/30-bitwise-and/problem
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
using namespace std;


uint32_t maxSetBit(uint32_t value) 
{
    for (int i=0; i < 32; i++) {
        uint32_t bitMask = 1 << i;   // 2^i
        if (bitMask > value) {
            return i-1;
        }
    }
    return 31;
}

uint32_t minUnsetBit(uint32_t value) 
{
    for (int i=0; i < 32; i++) {
        uint32_t bitMask = 1 << i;   // 2^i
        if ((bitMask & value) == 0) {
            return i;
        }
    }
    return 32;
}

void unitTest()
{
    assert(minUnsetBit(0) == 0);
    assert(minUnsetBit(1) == 1);
    assert(minUnsetBit(2) == 0);
    assert(minUnsetBit(0xff) == 8);

    //assert(maxSetBit(0) == 0);
    assert(maxSetBit(1) == 0);
    assert(maxSetBit(2) == 1);
    assert(maxSetBit(0xff) == 7);
    assert(maxSetBit(0xa0) == 7);
}

int findMax(int n, int k) 
{
    uint32_t k_MSB_1 = maxSetBit(k); // MSB set to 1 in k


    // Iteratively figure out a "target" value that is as close
    //  to "k" as possible. 
    // To reach a target value, it is best to use 
    //    a=target with 0th bit set to 0
    //    b=target with 0th bit set to 1 
    // Above approach will allow us to get closest to k while using 
    //  minimal "n". 
    // This approach works until we reach 0th bit. Then we can set
    //   a = 0th bit set to 1
    //   b = find rightmost 0th bit and change that to 1
    //
    uint32_t target = 0;

    for (int i=k_MSB_1; i > 0; i--) {
        int newVal = 1 << i; // ith bit is set to 1

        uint32_t newTarget = target + newVal;

        if (newTarget < k) {
            if (newTarget < n) { // same as: b=newTarget+1; b <= n
                target = newTarget;
            }
        } 
    }

    // Check if we can set 0th bit to 1
    {
        uint32_t newTarget = target | 1;
        uint32_t k_LSB_0 = minUnsetBit(newTarget);
        uint32_t b = newTarget | (1 << k_LSB_0); 
        if ((newTarget < k) && (b <= n)) {
            return newTarget;
        }
    }

    return target;
}


int main() 
{
    unitTest();

    int numTest;
    cin >> numTest;
    for (;numTest > 0; numTest--) {
        int n,k;
        cin >> n >> k;
        cout << findMax(n,k) << endl;
    }
    return 0;
}

