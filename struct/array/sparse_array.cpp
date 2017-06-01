//https://www.hackerrank.com/challenges/sparse-arrays

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
    int numEntries; 
    cin >> numEntries;
    
    unordered_map<string,int> dict;
    for (;numEntries > 0; numEntries--) {
        string entry;
        cin >> entry;

        if (dict.find(entry) == dict.end()) {
            dict[entry] = 1;
        } else{
            dict[entry]++;
        }
    }

    int numQueries;
    cin >> numQueries; 
    for (;numQueries > 0; numQueries--) {
        string query;
        cin >> query; 

        cout << dict[query] << endl;
    }

}
