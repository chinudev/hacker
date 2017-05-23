//https://www.hackerrank.com/challenges/big-sorting
#include <iostream>
#include <string>
#include <vector> 
#include <algorithm> 


using namespace std;

bool bigSort(const string& a, const string& b) 
{
	if (a.length() < b.length()) return true;
	if (a.length() > b.length()) return false;
	for (int i=0; i < a.length(); i++) {
		if (a[i] < b[i]) return true;
		if (a[i] > b[i]) return false;
		// if equal, check next digit
	}
	return false;
}

int main(){
    int n;
    cin >> n;
    vector<string> unsorted(n);
    for(int unsorted_i = 0; unsorted_i < n; unsorted_i++){
       cin >> unsorted[unsorted_i];
    }
	cout << "done reading" << endl;
	sort(unsorted.begin(), unsorted.end(), bigSort);
	for (string& elem : unsorted) {
		cout << elem << endl;
	}
    // your code goes here
    return 0;
}

