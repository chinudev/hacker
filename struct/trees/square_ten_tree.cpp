// https://www.hackerrank.com/challenges/square-ten-tree

#include <iostream>
#include <vector> 
#include <string>
#include <assert.h>

using namespace std;

struct SeqNode 
{
    SeqNode(int level_, int count_) : level(level_), count(count_) {}
    SeqNode() : level(0), count(0) {}
    int level;
    int count;
};


// return number = number - 1 and fill with leading zeros to match supplied length
string adjustLeftString(const string number, int length) 
{
    // fill with 0s
    string output(length, '0');  
    int offset = length - number.length();

    // subtract 1 and copy over to output string 
    int carry=-1;
    for (int index=number.length()-1; index >=0; index--) {
        int digit = number[index] - '0';
        digit += carry;

        if (digit < 0) {
            assert(digit == -1);
            digit = 9;
            carry=-1;
        } else {
            carry=0;
        }
        output[offset+index] = char(digit + '0');
    }
    assert(carry == 0);

    return output;
}


vector<pair<int,int>> findMinSequence( const string leftNum, const string rightNum) 
{
    vector<pair<int,int>> seqVector;
    //cout << "Processing " << leftNum << " " << rightNum << endl;

    int offset = rightNum.length() - leftNum.length();
    int leftIndex = leftNum.length()-1;
    int rightIndex = rightNum.length()-1;


    // MSDdiff is the most significant digit that is different between the 
    //  two numbers. For 9 1234, it is digit 0. For 1230 1234, it is digit 3
    int MSDdiff=-1; 
    if (offset > 0) {
        MSDdiff=0;
    } else {
        for (int i=0; i<rightNum.length(); i++) {
            if (leftNum[i] != rightNum[i]) {
                MSDdiff=i; 
                break;
            }
        }
    }
    // MSD diff == -1 means two nums are same
    //cout << "   MSD digit = " << MSDdiff << " offset " << offset << endl;

    if (MSDdiff == -1) {
        //cout << "   Operation level 0 count 1" << endl;
        seqVector.push_back({0,1});
        return seqVector;
    }
    assert(MSDdiff >= 0);

    int carry=0;
    int level=0;

    // go from right to left, switching leftNum digits to 0
    for (; rightIndex > MSDdiff; leftIndex--, rightIndex--, level++) {
        int leftDigit = carry;
        if (leftIndex >= 0) leftDigit += leftNum[leftIndex] - '0';

        int count;
        if (level == 0) {
            if (leftDigit < 2) {
                if (leftDigit == 0) count=1;
                if (leftDigit == 1) count=0;
                carry=0;
            } else {
                assert(leftDigit < 10);
                carry=1;
                count=11-leftDigit;
            }
        } else {
            if (leftDigit == 0) {
                carry=0;
                count=0;
            } else {
                carry=1;
                count=10-leftDigit;
            }
        }
        //cout << "   Operation level " << level << " count " << count << " carry " << carry << endl;
        if (count > 0) seqVector.push_back({level,count});
    }


    // Handle MSD digit 
    {
        int leftDigit = carry;
        if (leftIndex >= 0) leftDigit += leftNum[leftIndex] - '0';
        if (level == 0) leftDigit--;
        int rightDigit = rightNum[rightIndex] - '0';
        int count = rightDigit-leftDigit;

        assert(count >= 0);
        //cout << "   MSD Operation level " << level << " count " << count << endl;
        if (count > 0) seqVector.push_back({level,count});
        rightIndex++; leftIndex++; level--;
    }

    // go left to right, going from 0 to digit in rightNum
    for (; rightIndex < rightNum.length(); leftIndex++, rightIndex++, level--) {
        int rightDigit = rightNum[rightIndex] - '0';

        //cout << "   Operation level " << level << " count " << rightDigit << endl;
        if (rightDigit > 0) { 
            if (seqVector.back().first == level) {
                //cout << "********combined*****" << endl;
                seqVector.back().second += rightDigit;
            } else {
                seqVector.push_back({level,rightDigit});
            }
        }
    }


    return seqVector;
}

void test() 
{
    /*
    cout << "100 " << adjustLeftString("100",3) << endl;
    cout << "100 " << adjustLeftString("100",5) << endl;
    cout << "99 " << adjustLeftString("99",2) << endl;
    cout << "99 " << adjustLeftString("99",5) << endl;
    */


    // Single element special case
    assert(findMinSequence("1", "1") == (vector<pair<int,int>>{{0,1}}));
    assert(findMinSequence("22222231", "22222231") == (vector<pair<int,int>>{{0,1}}));

    // level 0 operations
    assert(findMinSequence("0", "9") == (vector<pair<int,int>>{{0,10}}));
    assert(findMinSequence("0", "10") == (vector<pair<int,int>>{{0,1},{1,1}}));
    assert(findMinSequence("0", "11") == (vector<pair<int,int>>{{0,1},{1,1},{0,1}}));
    assert(findMinSequence("1", "9") == (vector<pair<int,int>>{{0,9}}));
    assert(findMinSequence("1", "10") == (vector<pair<int,int>>{{1,1}}));
    assert(findMinSequence("1", "11") == (vector<pair<int,int>>{{1,1},{0,1}}));

    assert(findMinSequence("2", "12") == (vector<pair<int,int>>{{0,11}}));
    assert(findMinSequence("2", "22") == (vector<pair<int,int>>{{0,9},{1,1},{0,2}}));
    assert(findMinSequence("12", "22") == (vector<pair<int,int>>{{0,11}}));

    assert(findMinSequence("5", "1422") == (vector<pair<int,int>>{{0,6},{1,9},{2,13},{1,2},{0,2}}));
    assert(findMinSequence("42", "1024") == (vector<pair<int,int>>{{0,9},{1,5},{2,9},{1,2},{0,4}}));

    assert(findMinSequence("22222231", "22222240") == (vector<pair<int,int>>{{1,1}}));
}

int main() 
{

    //test();

    string leftNum, rightNum;
    cin >> leftNum >> rightNum;

    vector<pair<int,int>> resultVector = findMinSequence(leftNum, rightNum);

    cout << resultVector.size() << endl;
    for (auto entry : resultVector) {
        cout << entry.first << " " << entry.second << endl;
    }

}
