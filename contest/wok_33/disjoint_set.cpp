
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class DisjointSet
{
public:
    vector<int> setVector;

public:
    DisjointSet(int size) : setVector(size) {
        for (int i=0; i < size; i++) {
            setVector[i] = i;
        }
    }

    // Return the set id for "x"
    int Find(int x) 
    {
        int setId = x;

        while (setVector[setId] != setId) setId = setVector[setId];

        // Flatten this path of the tree
        for (int id=x; id != setId; ) {
            int nextId = setVector[id];
            setVector[id] = setId;
            id = nextId;
        }

        return setId;
    }

    void Union(int x, int y) 
    {
        if ((setVector[x] == 0) && (setVector[y] == 0)) {
            setVector[x] = x;
            setVector[y] = x;
            return;
        }
        if (setVector[x] == 0) {
            setVector[x] = y;
            return;
        }
        if (setVector[y] == 0) {
            setVector[y] = x;
            return;
        }
        int xSet = Find(x);
        int ySet = Find(y);
        if (xSet != ySet) setVector[ySet] = xSet;
    }

    void Print() 
    {
        cout << "Print set" << endl;
        for (int i=0; i < setVector.size(); i++) {
            cout << "** " << i << " " << Find(i) << endl; 
        }
    }

};


void testSet() 
{
    DisjointSet dset(10);

    assert(dset.Find(1) == 1);

    dset.Union(0,1);
    assert(dset.Find(1) == dset.Find(0));

    // Make 3 sets
    dset.Union(2,3);
    dset.Union(4,5);
    assert(dset.Find(1) != dset.Find(2));
    assert(dset.Find(0) != dset.Find(4));

    // Combine the 3 sets
    dset.Union(1,4);
    dset.Union(2,5);
    assert(dset.Find(0) == dset.Find(1));
    assert(dset.Find(0) == dset.Find(2));
    assert(dset.Find(0) == dset.Find(3));
    assert(dset.Find(0) == dset.Find(4));
    assert(dset.Find(0) == dset.Find(5));

    cout << " all test pass" << endl;

}


int main() 
{
    testSet();

}

