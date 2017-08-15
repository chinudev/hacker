#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

// search for values =k. If there is no value = k, then return the next lowest 
//  value. If all values are > k, return -1 
int bsearch(const vector<int> numVec,int k)
{
    int left = 0;
    int right = numVec.size()-1;

    while (left < right) {
        int center = (left+right)/2;
        if (numVec[center] == k) return center;
        if (numVec[center] > k) {
            right = center - 1;
        } else {
            if (numVec[center+1] <= k) left = center+1;
            else return left;
        }
    }
    if (numVec[left] > k) return left-1;
    return left;
}

void test() 
{
    assert(0  == bsearch({-4,-1,0,1,4,6,9,10},-2));
    assert(0  == bsearch({-4,-1,0,1,4,6,9,10},-4));
    assert(-1 == bsearch({-4,-1,0,1,4,6,9,10},-5));
    assert(4  == bsearch({-4,-1,0,1,4,6,9,10}, 4));
    assert(4  == bsearch({-4,-1,0,1,4,6,9,10}, 5));
    assert(5  == bsearch({-4,-1,0,1,4,6,9,10}, 6));
    assert(7  == bsearch({-4,-1,0,1,4,6,9,10}, 10));
    assert(7  == bsearch({-4,-1,0,1,4,6,9,10}, 11));

}

int main()
{
    test();

}
