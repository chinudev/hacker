// https://www.hackerrank.com/challenges/crush
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    long numEntries, numOp;
    cin >> numEntries >> numOp;
    
    vector<long long> store(numEntries,0); 
    for (long i=0; i<numOp; i++) {
        long long start,end,adder;
        cin >> start >> end >> adder;
        store[start-1] += adder;
        if (end < numEntries) {
            store[end] -= adder;    
        }
    }
    long long runningTotal=0;
    long long maxValue=0;
    for (auto value: store) {
        runningTotal += value;
        maxValue = max(runningTotal,maxValue);
    }
    cout << maxValue;
  
    return 0;
}
