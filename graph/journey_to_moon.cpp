// https://www.hackerrank.com/challenges/journey-to-the-moon
//
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std; 


int main()
{ 
    long numPeople, numPairs;

    cin >> numPeople >> numPairs;

    vector<long> countryPopulation;     // Tracks population for each country
                                        // population<0 means this country has been
                                        // sometime country have to be combined. in that 
                                        //  case one of the country will point to another 
                                        //  by using -ve value of pointed country's index

    vector<long> people(numPeople,-1);  // Tracks country people belong to. 
                                        // Initially people belong to no country (-1)

    long countryCount=0;   // Index of next country that will be created
                           // also count of country created so far.


    for (long i = 0; i < numPairs; ++i) {
        long a, b;
        cin >> a >> b;

        if ((people[a] == -1) && (people[b] == -1)) {
            // New country
            people[a]=countryCount;
            people[b]=countryCount;
            countryPopulation.push_back(2);    // create new country with 2 people
            countryCount++;
        } else {
            if ((people[a] != -1) && (people[b] != -1)) {
                // country are being combined 
                assert(people[a] == people[b]);
            } else if (people[a] != -1) {
                long country = people[a];
                people[b]=country;
                countryPopulation[country]++;
            } else if (people[b] != -1) {
                long country = people[b];
                people[a]=country;
                countryPopulation[country]++;
            } else {
                assert(1);  // should never reach here
            }

        }
    }

    // answer we are looking for
    long long numCombos=0;

    // we will keep reducing pendingPopulation as we process each country
    long long pendingPopulation=numPeople;

    // Iterate through all countries 
    for (long i=0; i < countryCount; i++) {
        //cout << "country " << i << " " << countryPopulation[i] << endl;
        pendingPopulation -= countryPopulation[i];
        numCombos += pendingPopulation*countryPopulation[i];
    }
    // iterate through people to find single person countries
    for (long i=0; i < numPeople ; i++) {
        //cout << "people " << i << " " <<  people[i] << endl;
        if (people[i] == -1) {
            pendingPopulation--;
            numCombos += pendingPopulation;
        }
    }

    cout << numCombos << endl;
    
    return 0;
}


/*

5 5 
0 1 
1 2 
2 3
3 4 
4 0
 */
