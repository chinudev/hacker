// https://www.hackerrank.com/challenges/square-ten-tree

#include <iostream>
#include <vector> 
#include <string>
#include <assert.h>
#include <stdint.h>

using namespace std;

typedef vector<pair<int,string>> SeqType;

char DigitMap[] = {'0','1','2','3','4','5','6','7','8','9'};


string addString(string first, string second) 
{
    // length of "first" should be greater than or equal to "second"
    if (first.length() < second.length()) {
        return addString(second, first);
    }

    int carry=0;
    int offset=first.length() - second.length();
    assert(offset >= 0);

    int firstDigit, secondDigit;
    for (int i=first.length()-1; i>=0; i--) {

        firstDigit = first[i]-'0';
        int secondIndex=i-offset;
        if (secondIndex >= 0) secondDigit = second[secondIndex] - '0' ;
        else secondDigit = 0;

        int add = carry + firstDigit  + secondDigit;
        if (add >= 10) {
            carry = 1;
            add = add % 10;
        } else {
            carry = 0;
        }
        first[i] = DigitMap[add];
    }
    if (carry) {
        return string("1").append(first);
    } else {
        return first;
    }
}

void test_add() 
{
    assert(addString("1", "1") == "2");
    assert(addString("12345", "1") == "12346");
    assert(addString("99", "112345") == "112444");
    assert(addString("99", "1") == "100");
}



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
        seqVector.push_back({0,to_string(diff+1)});
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
        if (diff > 0) seqVector.push_back({0,to_string(diff)});
        level++; leftIndex--;rightIndex--;
    }

    //Go from level 1 to MaxDiffLevel-1
    
    string stringBuffer;
    stringBuffer.reserve(512*1024);

    for (; level < MaxDiffLevel; level++) {
        int digitsInLevel = 1<<(level-1);
        stringBuffer.clear();

        for (int charIndex=digitsInLevel; charIndex > 0; charIndex--) {
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

            stringBuffer +=char(diff + '0');

            leftIndex--; rightIndex--;
        }
        auto rbegin = stringBuffer.rbegin();
        auto rend = stringBuffer.rend();
        while ((rbegin != rend) && *rbegin == '0') rbegin++;
        if (rbegin != rend) {
            string levelCountStr(rbegin,rend);
            seqVector.push_back({level,levelCountStr});
            //cout << "   Operation level " << level << " count :" << levelCountStr << endl;
        }

    }

    // Handle MaxDiffLevel 
    {
        int tempLeftIndex = leftIndex+1; 
        int tempRightIndex = rightIndex+1; 

        stringBuffer.clear();

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

            stringBuffer +=char(diff + '0');

            leftIndex--; rightIndex--;
            if (rightIndex < 0) break;
        }
        auto rbegin = stringBuffer.rbegin();
        auto rend = stringBuffer.rend();
        while ((rbegin != rend) && *rbegin == '0') rbegin++;
        if (rbegin != rend) {
            string levelCountStr(rbegin,rend);
            seqVector.push_back({level,levelCountStr});
            //cout << "   Operation levelx " << level << " count :" << levelCountStr << endl;
        } 

        level--;
        rightIndex = tempRightIndex;
        leftIndex = tempRightIndex;
    }

    // Go from level MaxDiffLevel-1 down to 0
    for (; level >= 0; level--) {
        int digitsInLevel;
        stringBuffer.clear();

        if (level == 0) digitsInLevel=1;
        else digitsInLevel = 1<<(level-1);

        for (; digitsInLevel > 0; digitsInLevel--) {
            //cout << "      level " << level << " left " << leftIndex << " right " << rightIndex << endl;
            int rightDigit = rightNum[rightIndex] - '0';

            stringBuffer +=char(rightDigit + '0');

            leftIndex++; rightIndex++;
        }

        auto begin = stringBuffer.begin();
        auto end = stringBuffer.end();
        while ((begin != end) && *begin == '0') begin++;

        if (begin != end) {
            string levelCountStr(begin,end);

            if (seqVector.back().first == level) {
                seqVector.back().second = addString(seqVector.back().second,levelCountStr);
            } else {
                seqVector.push_back({level,levelCountStr});
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

    test_add();

    // Single element special case
    testcase("1", "1",SeqType{{0,"1"}});

    // Single element special case
    testcase("1", "1", SeqType{{0,"1"}});
    testcase("22222231", "22222231", SeqType{{0,"1"}});


    testcase("0", "9", SeqType{{0,"10"}});
    testcase("0", "10", SeqType{{0,"1"},{1,"1"}});
    testcase("0", "11", SeqType{{0,"1"},{1,"1"},{0,"1"}});
    testcase("1", "9", SeqType{{0,"9"}});
    testcase("1", "10", SeqType{{1,"1"}});
    testcase("1", "11", SeqType{{1,"1"},{0,"1"}});

    testcase("2", "12", SeqType{{0,"11"}});
    testcase("2", "22", SeqType{{0,"9"},{1,"1"},{0,"2"}});
    testcase("12", "22", SeqType{{0,"11"}});

    testcase("980001", "990000", SeqType{{3,"1"}});

    testcase(   "24274044",    "99906984", SeqType{{0,"7"},{1,"5"},{2,"59"},{3,"7562"},{2,"69"}, {1,"8"},{0,"4"}});
    testcase(  "124274044",   "199906984", SeqType{{0,"7"},{1,"5"},{2,"59"},{3,"7562"},{2,"69"}, {1,"8"},{0,"4"}});
    testcase("99124274044", "99199906984", SeqType{{0,"7"},{1,"5"},{2,"59"},{3,"7562"},{2,"69"}, {1,"8"},{0,"4"}});
    testcase(    "4274044",     "9906984", SeqType{{0,"7"},{1,"5"},{2,"59"},{3,"562"}, {2,"69"}, {1,"8"},{0,"4"}});

    testcase("5", "1422", SeqType{{0,"6"},{1,"9"},{2,"13"},{1,"2"},{0,"2"}});
    testcase("42", "1024", SeqType{{0,"9"},{1,"5"},{2,"9"},{1,"2"},{0,"4"}});

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
