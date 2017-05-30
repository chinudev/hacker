//https://www.hackerrank.com/challenges/closest-numbers

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    unsigned long long numEntries; 
    cin >> numEntries; 
    
    vector<long long> numVector;
    for (auto i=0; i<numEntries; i++) {
        long long number;
        cin >> number;
        numVector.push_back(number);
    }
    sort(numVector.begin(), numVector.end());
    
    // first pass to find the smallest delta 
    long long smallestDiff=10000000;
    for (auto i=1; i<numEntries-1;i++) {
        long long diff = numVector[i]-numVector[i-1];
        if (diff < smallestDiff) {
            smallestDiff=diff;
        }
    }
       
    // second pass to print 
    for (auto i=1; i<numEntries-1;i++) {
        long long diff = numVector[i]-numVector[i-1];
        if (diff == smallestDiff) {
            cout << numVector[i-1] << " " << numVector[i] << " ";
        }
    }
    cout << endl;
        
    return 0;
}

