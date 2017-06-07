#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <assert.h>

using namespace std;

bool isValid(const string str) 
{
    vector<int> letterCount(26,0);
    for (auto letter : str) {
        letterCount[letter - 'a']++;
    }
    int num1=-1; 
    int num1Count=0;
    int num2=-1; 
    int num2Count=0;

    for (auto count : letterCount) {
        if (count > 0) {
            if (num1 == -1) {
                num1 = count;
                num1Count=1;
                continue;
            }
            if (count == num1) {
                num1Count++;
                continue;
            }

            if (num2 == -1) {
                num2 = count;
                num2Count=1;
                continue;
            }
            if (count == num2) {
                num2Count++;
                continue;
            }

            return false;
        }
    }
    assert(num1 > 0);

    if (num2 == -1) return true;
    if ((num1Count > 1) && (num2Count > 1)) return false;

    if (num2Count == 1) {
        swap(num1Count, num2Count);
        swap(num1, num2);
    }

    // There is only one instance of num1 
    assert(num1Count == 1); 
    assert(num2Count >= num1Count);
    assert(num1 != num2);

    if (num1 == 1) return true;         // caaabbb or aaabbbc

    if (num1 < num2) {
        // Only way to match is to delete num2
        if (num2Count > 1) return false;    // aabbbccc
        if (num2 - num1 <= 1) return true;  // aabbb
        else return false;                  // aabbbb
    }

    if (num1 - num2 == 1)  return true;  // aaabbcc
    if ((num2Count == 1) && num2 == 1) return true;  // aaab

    return false;
}


void unitTest() 
{
    // already valid
    assert(isValid("a") == true);
    assert(isValid("bbbbb") == true);
    assert(isValid("ababab") == true);

    // Delete one to make a match char
    assert(isValid("aaabb") == true);
    assert(isValid("aabbb") == true);
    assert(isValid("aaabbcc") == true);
    assert(isValid("aabbccc") == true);

    // Delete the lone char to eliminate mismatch
    assert(isValid("abbb") == true);
    assert(isValid("abbcc") == true);
    assert(isValid("bbccd") == true);
    assert(isValid("aaab") == true);

    assert(isValid("aaaabb") == false);
    assert(isValid("aabbbb") == false);

    assert(isValid("abbccc") == false);

}

int main() 
{
    //unitTest();
 
    string s;
    cin >> s;
    if (isValid(s)) cout << "YES";
    else cout << "NO";
}
