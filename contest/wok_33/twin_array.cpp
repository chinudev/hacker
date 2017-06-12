// https://www.hackerrank.com/contests/w33/challenges/twin-arrays

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <stdint.h>

using namespace std;

// Helper class to track the min 2 values
//
struct TwinMinStruct 
{
    TwinMinStruct() :
        min1Value(INT32_MAX),
        min2Value(INT32_MAX),
        min1Index(-1),
        min2Index(-1)
    {}

    // Call this for every entry in the array 
    void update(int value, int index) 
    {
        if (value <= min1Value) {
            min2Value = min1Value;
            min2Index = min1Index;
            min1Value = value;
            min1Index = index;
        } else if (value <= min2Value) {
            min2Value = value;
            min2Index = index;
        }
    }

    void print() {
        cout << " Min1 (" << min1Value << "," << min1Index << ")";
        cout << " Min2 (" << min2Value << "," << min2Index << ")";
        cout << endl;
    }

    int min1Value;
    int min1Index;

    int min2Value;
    int min2Index;
};


int twinArrays(vector <int> ar1, vector <int> ar2)
{
    
    TwinMinStruct ar1Min;
    TwinMinStruct ar2Min;

    for (int i=0; i < ar1.size(); i++) ar1Min.update(ar1[i],i);
    for (int i=0; i < ar2.size(); i++) ar2Min.update(ar2[i],i);
    
    //cout << "ar1 = "; ar1Min.print();
    //cout << "ar1 = "; ar2Min.print();

    if (ar1Min.min1Index != ar2Min.min1Index) {
        return ar1Min.min1Value + ar2Min.min1Value;
    }

    int result = min(ar1Min.min1Value + ar2Min.min2Value, 
                     ar1Min.min2Value + ar2Min.min1Value);

    return result;

}

void test()
{
    assert(3 == twinArrays({1,1}, {2,2}));
    assert(4 == twinArrays({1,4}, {1,3}));
    assert(3 == twinArrays({2,1}, {4,1}));
    assert(3 == twinArrays({1,5,4,3,2}, {1,5,4,3,2}));
    assert(2 == twinArrays({1,5,4,3,2}, {5,1,4,3,2}));
}

int main() 
{
    //test();


    int n;
    cin >> n;
    vector<int> ar1(n);
    for(int ar1_i = 0; ar1_i < n; ar1_i++){
       cin >> ar1[ar1_i];
    }
    vector<int> ar2(n);
    for(int ar2_i = 0; ar2_i < n; ar2_i++){
       cin >> ar2[ar2_i];
    }
    int result = twinArrays(ar1, ar2);
    cout << result << endl;
    return 0;
}

