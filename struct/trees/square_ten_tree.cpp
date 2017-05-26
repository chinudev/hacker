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


void findMinSequence(
        const string leftNumIn, 
        const string rightNum, 
        vector<SeqNode>& seqVector) 
{
    string leftNum = adjustLeftString(leftNumIn, rightNum.length());
    assert(leftNum.length() == rightNum.length());

    // Split work into two segments e.g. 
    //   0444 - 5886 = 0444-5000 and 5000-5886
    //
    string midNum(rightNum.length(),'0');
    for (int index=0; index < rightNum.length(); index++) {
        midNum[index] = rightNum[index];
        if (leftNum[index] != rightNum[index])  break;
    }

    /*
    cout << "Left  " << leftNum << endl;
    cout << "Mid   " << midNum << endl;
    cout << "Right " << rightNum << endl;
    */

    // Process digits from right to left to move from leftNum to midNum
    // for each digit position we find number movements required to 
    //   move leftNum to match midNum
    //  
    int carry=0;
    for (int index=midNum.length(); index >= 0; index--) {

        // level = 0 for ones, 1 for tens, 2 for hundreds etc.
        int currLevel = midNum.length() - 1 - index;
        int midDigit = midNum[index] - '0';
        int leftDigit = carry + (leftNum[index] - '0');

        if (leftDigit == midDigit) {
            // no operations needed since this digit is same for leftNum and rightNum
            carry=0;
        } else {
            if (leftDigit < midDigit) {
                carry=0;
                seqVector.push_back(SeqNode(currLevel, midDigit-leftDigit));
                break;
            } else {
                if (midDigit != 0) cout << index << endl;
                assert(midDigit == 0);

                carry=1;
                if (leftDigit < 10) seqVector.push_back(SeqNode(currLevel, 10-leftDigit));
            }
        }
    }

    // Process digits from left to right to move from midNum to rightNum
    //  
    for (int index=0; index < rightNum.length(); index++) {

        // level = 0 for ones, 1 for tens, 2 for hundreds etc.
        int currLevel = midNum.length() - 1 - index;

        int midDigit = midNum[index] - '0';
        int rightDigit = rightNum[index] - '0';

        if (midDigit == rightDigit) {
            // no operations needed since this digit is same for leftNum and rightNum
        } else {
            assert(midDigit < rightDigit);
            if (seqVector.back().level == currLevel) {
                seqVector.back().count += rightDigit-midDigit;
            } else {
                seqVector.push_back(SeqNode(currLevel, rightDigit-midDigit));
            }
        }
    }
}

void test() 
{
    cout << "100 " << adjustLeftString("100",3) << endl;
    cout << "100 " << adjustLeftString("100",5) << endl;
    cout << "99 " << adjustLeftString("99",2) << endl;
    cout << "99 " << adjustLeftString("99",5) << endl;

}

int main() 
{

    string leftNum, rightNum;
    cin >> leftNum >> rightNum;

    vector<SeqNode> resultVector;
    findMinSequence(leftNum, rightNum, resultVector);

    cout << resultVector.size() << endl;
    for (SeqNode entry : resultVector) {
        cout << entry.level << " " << entry.count << endl;
    }
}
