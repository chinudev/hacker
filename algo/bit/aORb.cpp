#include <iostream>
#include <array>
#include <bitset>
#include <assert.h>
#include <stdint.h>
#include <map>

using namespace std;


uint32_t numBits(uint32_t num) 
{
    uint32_t count=0;
    while (num) {
        if (num & 1) count++;
        num = num >> 1;
    }
    return count;
}
void test()
{
    assert(0 == numBits(0));
    assert(1 == numBits(1));
    assert(2 == numBits(9));
    assert(4 == numBits(15));
}

class BitChanges 
{
    map<char,int>  hexToIntMap;
    array<char,16> intToHexMap;
    array<array<pair<uint32_t,uint32_t>, 16> ,16> aToC_Cache;
    array<array<array<pair<uint32_t,uint32_t>, 16>, 16>, 16> bToC_Cache;

public:
    BitChanges() {

        for (int i=0; i < 16; i++) {
            char c;
            if (i < 10) c = '0'+i;
            else c = 'A'+i-10;
            hexToIntMap[c] = i;
            intToHexMap[i] = c;
        }

        // We will only flip bits that are 1 in A but 0 in C. 
        // For B we will flip 1->0 and also any 0->1 if required.

        // Pre-compute transform for A in two dimensional array
        //   transform[A][C]= pair(bitFlips, transformedA)
        for (uint32_t A=0; A <16; A++) {
            for (uint32_t C=0; C <16; C++) {
                uint32_t newA = A & C;
                uint32_t bitFlips = numBits(A) - numBits(newA);
                aToC_Cache[A][C] = make_pair(bitFlips, newA);
            }
        }

        // Pre-compute transform for B in three dimensional array
        //   transform[A][B][C]= pair(bitFlips, transformedB)
        for (uint32_t A=0; A <16; A++) {
            for (uint32_t B=0; B <16; B++) {
                for (uint32_t C=0; C <16; C++) {
                    // assume A transmformed
                    uint32_t newA = A & C;

                    // compute 1->0 flips for B->C
                    uint32_t bitFlips = aToC_Cache[B][C].first;
                    uint32_t newB = aToC_Cache[B][C].second;

                    // Figure out number of 0->1 flips for B
                    uint32_t abCombo = newA | newB;
                    uint32_t oneFlips = C & ~abCombo;
                    bitFlips += numBits(oneFlips);
                    newB = newB | oneFlips;

                    bToC_Cache[A][B][C] = make_pair(bitFlips, newB);
                }
            }
        }
    }


    int findBitChanges(string& aStr, 
                       string& bStr, 
                       const string& cStr,
                       uint32_t maxFlips) 
    {
        int bitFlips = 0;
        for (int i=0; i < aStr.size(); i++) {
            // a -> c
            int aChar = hexToIntMap[aStr[i]];
            int bChar = hexToIntMap[bStr[i]];
            int cChar = hexToIntMap[cStr[i]];

            bitFlips += aToC_Cache[aChar][cChar].first;
            aStr[i] = intToHexMap[aToC_Cache[aChar][cChar].second];

            bitFlips += bToC_Cache[aChar][bChar][cChar].first;
            bStr[i] = intToHexMap[bToC_Cache[aChar][bChar][cChar].second];
        }

        if (bitFlips >= maxFlips) return bitFlips; 
        uint32_t bitsLeft = maxFlips - bitFlips;

        // minimize values for A using any leftover bitFlips
        for (int i=0; i < aStr.size(); i++) {
            int aChar = hexToIntMap[aStr[i]];
            int bChar = hexToIntMap[bStr[i]];
            if (aChar == 0) continue;
            int cChar = hexToIntMap[cStr[i]];

            for (int bitMask = 8; bitMask > 0; bitMask = bitMask >> 1){
                if (bitsLeft == 0) break; 
                if (aChar & bitMask) {
                    assert(cChar & bitMask);
                    if (bChar & bitMask) {
                        aChar = aChar & (~bitMask);
                        bitsLeft--;
                    } else {
                        if (bitsLeft >= 2) {
                            aChar = aChar & (~bitMask);
                            bChar = bChar | bitMask;
                            bitsLeft -= 2;
                        }
                    }
                }
            }
            aStr[i] = intToHexMap[aChar];
            bStr[i] = intToHexMap[bChar];
            if (bitsLeft == 0) break; 
        }
        return maxFlips - bitsLeft;
    }
};




int main()
{
    test();

    int numTest;
    cin >> numTest;

    BitChanges bitChanges;
    for (;numTest > 0; numTest--) {
        uint64_t k;
        string a,b,c;

        cin >> k >> a >> b >> c;
        int bitFlips = bitChanges.findBitChanges(a,b,c,k);
        if (bitFlips <= k) {
            a.erase(0, min(a.find_first_not_of('0'), a.size()-1));
            b.erase(0, min(b.find_first_not_of('0'), b.size()-1));
            
            cout << a << endl;
            cout << b << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}
