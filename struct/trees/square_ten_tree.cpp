// https://www.hackerrank.com/challenges/square-ten-tree

#include <iostream>
#include <vector> 
#include <string>
#include <assert.h>
#include <stdint.h>

using namespace std;

typedef vector<pair<int,uint64_t>> SeqType;


void findMinSequence( const string leftNum, const string rightNum, SeqType& seqVector) 
{
    //cout << "Processing " << leftNum << " " << rightNum << endl;

    int offset = rightNum.length() - leftNum.length();


    // MSDdiff is the most significant digit that is different between the 
    //  two numbers. For 9 1234, it is digit 0. For 1230 1234, it is digit 3
    int diffIndex=-1; 
    if (offset > 0) {
        diffIndex=0;
    } else {
        for (int i=0; i<rightNum.length(); i++) {
            if (leftNum[i] != rightNum[i]) {
                diffIndex=i; 
                break;
            }
        }
    }
    int diffDigit = rightNum.length()-diffIndex-1;

    // Special handling
    //   diffIndex == -1 means two nums are same.
    //   diffDigit==0 means only least-signficant digit is different 
    if ((diffIndex == -1)  || (diffDigit == 0)) {
        assert(rightNum[rightNum.length()] >= leftNum[leftNum.length()]);
        int diff = rightNum[rightNum.length()-1] - leftNum[leftNum.length()-1];
        //cout << "   Operation level 0 count " << diff+1 <<  endl;
        seqVector.push_back({0,diff+1});
        return;
    }
    assert(diffDigit > 0);

    // Level : Number : Digits
    //    0      10^0  [1,1]
    //    1      10^1  [1,10]
    //    2      10^2  [1,100]
    //    3      10^4  [1,10'000]
    //    4      10^8  [1,100'000'000]
    //
    int MaxDiffLevel=0; 
    for (int pow2=1; diffDigit >= pow2; pow2 *= 2) MaxDiffLevel++;
    //cout << "   Diff digit = " << diffDigit << " diffLevel " << MaxDiffLevel << endl;


    int carry=0;
    int level=0;
    int leftIndex = leftNum.length()-1;
    int rightIndex = rightNum.length()-1;

    //Handle level 0. 
    {
        int leftDigit = leftNum[leftNum.length()-1] - '0';
        int diff = 11 - leftDigit;
        if (diff > 9)  diff = diff % 10;
        else carry=1;

        //cout << "   Operation level 0 count " << diff <<  endl;
        if (diff > 0) seqVector.push_back({0,diff});
        level++; leftIndex--;rightIndex--;
    }

    //Go from level 1 to MaxDiffLevel-1
    for (; level < MaxDiffLevel; level++) {
        uint64_t levelCount=0;
        uint64_t digitMultiple=1;
        int digitsInLevel = 1<<(level-1);
        for (; digitsInLevel > 0; digitsInLevel--) {
            //cout << "      level " << level << " left " << leftIndex << " right " << rightIndex << endl;
            int leftDigit=carry; 
            if (leftIndex >= 0) leftDigit += leftNum[leftIndex] - '0';

            int diff = 10 - leftDigit;
            if (diff > 9) {
                diff = diff % 10;
                carry = 0;
            } else {
                carry = 1;
            }

            levelCount = levelCount + digitMultiple*diff;
            digitMultiple = digitMultiple*10;

            leftIndex--; rightIndex--;
        }
        //cout << "   Operation level " << level << " count " << levelCount <<  endl;
        if (levelCount > 0) seqVector.push_back({level,levelCount});
    }

    // Handle MaxDiffLevel 
    {
        int tempLeftIndex = leftIndex+1; 
        int tempRightIndex = rightIndex+1; 

        uint64_t levelCount=0;
        uint64_t digitMultiple=1;
        int digitsInLevel = 1<<(level-1);
        for (; digitsInLevel > 0; digitsInLevel--) {
            int leftDigit=carry; 
            if (leftIndex >= 0) leftDigit += leftNum[leftIndex] - '0';
            int rightDigit =  rightNum[rightIndex] - '0'; 

            int diff = 10 + rightDigit - leftDigit;
            if (diff > 9) {
                diff = diff % 10;
                carry = 0;
            } else {
                carry = 1;
            }

            //cout << "      level " << level << " left " << leftIndex << " right " << rightIndex  << " diff " << diff << endl;
            levelCount = levelCount + digitMultiple*diff;
            digitMultiple = digitMultiple*10;

            leftIndex--; rightIndex--;
            if (rightIndex < 0) break;
        }
        //cout << "   Operation levelx " << level << " count " << levelCount <<  endl;
        if (levelCount > 0) seqVector.push_back({level,levelCount});

        level--;
        rightIndex = tempRightIndex;
        leftIndex = tempRightIndex;
    }

    // Go from level MaxDiffLevel-1 down to 0
    for (; level >= 0; level--) {
        uint64_t levelCount=0;
        uint64_t digitMultiple=1;
        int digitsInLevel;
        if (level == 0) digitsInLevel=1;
        else digitsInLevel = 1<<(level-1);

        for (; digitsInLevel > 0; digitsInLevel--) {
            //cout << "      level " << level << " left " << leftIndex << " right " << rightIndex << endl;
            int rightDigit = rightNum[rightIndex] - '0';
            levelCount = levelCount*10 + rightDigit;

            leftIndex++; rightIndex++;
        }
        //cout << "   Operation level " << level << " count " << levelCount <<  endl;
        if (levelCount > 0) {
            if (seqVector.back().first == level) {
                seqVector.back().second += levelCount;
            } else {
                seqVector.push_back({level,levelCount});
            }
        }
    }


    return;
}


void testcase(const string leftNum, const string rightNum, const SeqType& expected) 
{
    //cout << "Comparing " << leftNum << " " << rightNum << endl;
    SeqType resultVector;
    findMinSequence(leftNum, rightNum, resultVector);
    assert(resultVector == expected);
    cout << "Passed " << leftNum << " " << rightNum << endl;

}


void test() 
{

    // Single element special case
    testcase("1", "1",SeqType{{0,1}});

    // Single element special case
    testcase("1", "1", SeqType{{0,1}});
    testcase("22222231", "22222231", SeqType{{0,1}});


    testcase("0", "9", SeqType{{0,10}});
    testcase("0", "10", SeqType{{0,1},{1,1}});
    testcase("0", "11", SeqType{{0,1},{1,1},{0,1}});
    testcase("1", "9", SeqType{{0,9}});
    testcase("1", "10", SeqType{{1,1}});
    testcase("1", "11", SeqType{{1,1},{0,1}});

    testcase("2", "12", SeqType{{0,11}});
    testcase("2", "22", SeqType{{0,9},{1,1},{0,2}});
    testcase("12", "22", SeqType{{0,11}});

    testcase("980001", "990000", SeqType{{3,1}});
    testcase("24274044", "99906984", SeqType{{0,7},{1,5},{2,59},{3,7562},{2,69}, {1,8},{0,4}});

    testcase("124274044", "199906984", SeqType{{0,7},{1,5},{2,59},{3,7562},{2,69}, {1,8},{0,4}});
    testcase("99124274044", "99199906984", SeqType{{0,7},{1,5},{2,59},{3,7562},{2,69}, {1,8},{0,4}});
    testcase("4274044", "9906984", SeqType{{0,7},{1,5},{2,59},{3,562},{2,69}, {1,8},{0,4}});

    testcase("5", "1422", SeqType{{0,6},{1,9},{2,13},{1,2},{0,2}});
    testcase("42", "1024", SeqType{{0,9},{1,5},{2,9},{1,2},{0,4}});

    /*
    testcase("124274044", "299906984", SeqType{{4,1}});
    testcase("22222231", "22222240", SeqType{{1,1}});
    */

}

int main() 
{

    //test();

    string leftNum, rightNum;
    cin >> leftNum >> rightNum;

    SeqType resultVector;
    findMinSequence(leftNum, rightNum, resultVector);

    cout << resultVector.size() << endl;
    for (auto entry : resultVector) {
        cout << entry.first << " " << entry.second << endl;
    }

}
