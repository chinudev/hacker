// https://www.hackerrank.com/challenges/find-the-median

#include <vector> 
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;


int partition(vector<int>& numVector, int left, int right)
{
    int pivotValue = numVector[right];
    int pivotIndex = left;

    for (int i=left; i <= right; i++) {
        if (numVector[i] <= pivotValue) {
            swap(numVector[i], numVector[pivotIndex]);
            pivotIndex++;
        }
    }
    return pivotIndex - 1;

}

int findNth(vector<int> numVector, int n)
{
    int left=0; 
    int right = numVector.size()-1;


    while (right-left > 0) {
        int pivot = partition(numVector, left, right);

        if (pivot == n) return numVector[pivot];
        if (pivot < n) left = pivot+1;
        else right = pivot - 1;            // pivot > n
    }
    assert(left == n);
    return numVector[left];

}

void test() 
{
    assert(3 == findNth({0,1,2,4,6,5,3}, 3));
    assert(3 == findNth({3}, 0));
    assert(2 == findNth({2,1,3}, 1));
}

int main() 
{
    test();
    int numEntries;
    cin >> numEntries;

    vector<int> numVector;
    for (; numEntries > 0; numEntries--) {
        int entry;
        cin >> entry;
        numVector.push_back(entry);
    }
    cout << findNth(numVector, int(numVector.size()/2)) << endl;
}
