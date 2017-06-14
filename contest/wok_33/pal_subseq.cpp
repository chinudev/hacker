#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;


// Tested with string and vector. 
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

void test()
{
    assert(1 == lps(vector<int>({1})));
    assert(1 == lps(vector<int>({1,2})));
    assert(2 == lps(vector<int>({2,2})));
    assert(2 == lps(vector<int>({2,2,1})));
    assert(2 == lps(vector<int>({9,2,2})));
    assert(2 == lps(vector<int>({9,2,2,1})));
    assert(3 == lps(vector<int>({2,1,2})));
    assert(5 == lps(vector<int>({1,7,2,8,3,9,2,1})));

    assert(1 == lps(string("1")));
    assert(1 == lps(string("12")));
    assert(2 == lps(string("22")));
    assert(2 == lps(string("221")));
    assert(2 == lps(string("922")));
    assert(2 == lps(string("9221")));
    assert(3 == lps(string("212")));
    assert(5 == lps(string("17283921")));
}
 
int main()
{
    test();

}


