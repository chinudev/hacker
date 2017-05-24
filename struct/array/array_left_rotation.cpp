#include <vector>
#include <iostream>

using namespace std;


int main()
{
	unsigned long numEntries, numRotation;

	cin >> numEntries >> numRotation;
	numRotation = numRotation % numEntries;

	vector<unsigned long> tempStore(numRotation);

	for (auto i=0; i<numRotation;i++) {
		cin >> tempStore[i];
	}

	for (auto i=0; i<numEntries-numRotation;i++) {
		unsigned long num;
		cin >> num;
		cout << num << " ";
	}
	for (auto i=0; i<numRotation;i++) {
		cout << tempStore[i] << " ";
	}
	cout << endl;

}

