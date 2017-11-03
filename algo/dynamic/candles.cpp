
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

using namespace std;


const uint32_t MOD = 1000*1000*1000 + 7;  // 10^9 + 7

class ColorCount
{
public:
    ColorCount(uint32_t maxColor) : colorId(-1), bitMask(0), MaxColor(maxColor) {
        NumSlots = 1 << maxColor;
        numVec = vector<int>(NumSlots,0);
    }
    void SetColor(uint32_t colorId_)  {
        colorId = colorId_;
        bitMask = 1 << colorId;
        numVec[bitMask] = 1;
    }
    bool IsEmpty() const {
        if (colorId < 0) return true;
        return false;
    }
    
    // return numcombos with all bit set to 1
    int GetCombos() {
        if (colorId < 0) return 0;
        return numVec.back();
    }

    void Add(const ColorCount& rhs) {
        assert(rhs.MaxColor == MaxColor);
        if (rhs.IsEmpty()) return;
        for (uint32_t i=0; i < NumSlots; i++) {
            uint32_t newSlot = i | bitMask;
            numVec[newSlot] = (numVec[newSlot] + rhs.numVec[i]) % MOD;
        }
    }
    void Print(){
        cout << "  [";
        for (int i=0; i < NumSlots; i++) {
            cout << numVec[i] << " ";
        }
        cout << "]" << endl;
    }

private:
    int colorId;
    int bitMask;
    int MaxColor;
    int NumSlots;
    vector<int> numVec;
};

int getNumSubseq(vector<pair<int,int>>& candleVec, int numColors)
{
    vector<ColorCount> candleCombos(candleVec.size(), ColorCount(numColors));

    uint32_t numCombos = 0;

    for (int i=0; i < candleVec.size(); i++) {
        uint32_t height = candleVec[i].first;
        uint32_t color = candleVec[i].second;
        candleCombos[i].SetColor(color-1);
        for (int j=0; j<i; j++) {
            if (candleVec[j].first < height) {
                candleCombos[i].Add(candleCombos[j]);
            }
        }
        //cout << i << " = ";
        //candleCombos[i].Print();
        numCombos = (numCombos + candleCombos[i].GetCombos()) % MOD;
    }
    return numCombos;
}


void test()
{
}

int main()
{
    test();
    
    int numEntry, numColors;
    cin >> numEntry >> numColors;

    vector<pair<int,int>> candleVec;

    for (; numEntry > 0; numEntry--) {
        int height, color;

        cin >> height >> color;
        candleVec.push_back(make_pair(height,color));

    }
    cout << getNumSubseq( candleVec, numColors) << endl;
    
}
