// https://www.hackerrank.com/challenges/abbr

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

using namespace std;



bool abbr(string& src, int srcIndex,
          string& target, int targetIndex,
          vector<vector<int>>& cache)
{
    if (cache[srcIndex][targetIndex] != -1) return cache[srcIndex][targetIndex];

    // can't transform if src string is smaller than target
    if (src.size() - srcIndex < target.size() - targetIndex) {
        cache[srcIndex][targetIndex] = 0;
        return false;
    }

    bool result=false;
    char srcChar = src[srcIndex];
    char targetChar = target[targetIndex];

    if (srcChar >= 'A' && srcChar <= 'Z') {
        if (target[targetIndex] == srcChar) {
            result = abbr(src,srcIndex+1,target,targetIndex+1, cache);
        } else {
            result = false;
        }
    } else {
        if ((srcChar - 'a') == (targetChar - 'A')) {
            result = abbr(src,srcIndex+1,target,targetIndex+1, cache);
        } 
        if (result == false) {
            result = abbr(src,srcIndex+1,target,targetIndex, cache);
        }
    }

    cache[srcIndex][targetIndex] = result;
    return result;
}

bool abbr(string src, string target)
{
    const int MAX_ENTRY = 1001;
    // -1 means uninitialized. 0 : false, 1 : true
    vector<vector<int>> cache(MAX_ENTRY, vector<int>(MAX_ENTRY, -1));

    cache[src.size()][target.size()]=1; // both empty strings

    return abbr(src, 0, target, 0, cache);
}


void unitTest()
{
    assert(false == abbr("abc","ABCD"));
    assert(true == abbr("abc","ABC"));
    assert(true == abbr("abc","BC"));
    assert(true == abbr("AaBAc","ABC"));
}

int main()
{
    //unitTest();

    int numQuery;
    cin >> numQuery;


    for (int q=0; q < numQuery; q++) {
        string strA, strB;
        cin >> strA >> strB;

        if (abbr(strA, strB)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

}
