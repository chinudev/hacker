
#include <iostream>
#include <vector>
#include <algorithm>
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


template <typename Container>
int lps(Container str)
{
    int length = str.size();

    // cache tracks length of max palindrome sequence
    //   length for string[i:j+1] is stored at cache[i][j] 
    vector< vector<int>> cache(length+1, vector<int>(length,0));

    // seed. all strings of length 1 are palindromes
    for (int i=0; i < length; i++) cache[i][i] = 1;

    // consider increasing lengths of strings
    for (int slength=2; slength <= length; slength++) {

        // consider string[i:j+1]
        for (int i=0; i < length; i++) {
            int j = i + slength - 1; 
            if (j >= length) break;

            if (str[i] == str[j]) {
                // 2 char string is a special case but since cache array is all 
                //  0s we don't need to handle it differently
                cache[i][j] = 2 + cache[i+1][j-1];
            } else {
                cache[i][j] = max(cache[i][j-1], cache[i+1][j]);
            }
        }
    }
    return cache[0][length-1];
}





int main() 
{

    int setSize, numMappings, stringSize;
    cin >> setSize >> numMappings >> stringSize;


    DisjointSet dset(setSize+1);
    for (; numMappings > 0; numMappings--) {
        int x,y;
        cin >> x >> y;
        dset.Union(x,y);
    }

    //dset.Print();

    vector<int> str(stringSize);
    for (int i=0; i < stringSize; i++) {
        int elem; 
        cin >> elem;
        str[i] = dset.Find(elem);
    }

    cout << lps(str) << endl;

}

