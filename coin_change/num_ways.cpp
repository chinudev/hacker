#include <bits/stdc++.h>

using namespace std;


long getWays(long n, vector<long> coinVector) 
{
        // Initialize to 0. index from 0 to n+1
        vector<long> waysForVal(n+1,0);
        waysForVal[0]=1;

        for (auto coinValue : coinVector) {
                for (auto i=0; i <= n-coinValue; i++) {
                        waysForVal[i+coinValue] += waysForVal[i];
                }
        }
        return waysForVal[n];

}


int main()
{
        cout << getWays(10,{2,3,5,10}) << endl;
}
