#include <vector>
#include <iostream>

using namespace std;

vector<int> stringVector;

void init()
{
        stringVector.push_back(0);
        int count=1;

        for (auto i=0;i<10;i++) {
                // Copy from string so far (index) to append a new 
                //  string 
                for (auto index=0; index < count; index++) {
                        stringVector.push_back(stringVector[index]?0:1);
                }
                count = count*2;
        }
}

int main()
{
        init();
        for (auto i:stringVector) cout << i;
        cout << endl;

        cout << "lenght = " << stringVector.size() << endl;
        cout << stringVector[2] << endl;
        cout << stringVector[5] << endl;
        cout << stringVector[7] << endl;
}
