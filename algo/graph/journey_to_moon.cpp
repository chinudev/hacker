// https://www.hackerrank.com/challenges/journey-to-the-moon
//
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std; 


class CountryNode 
{
public: 
    CountryNode(long long pop) : parent(nullptr), processed(false), population(pop) {}

public:
    CountryNode* parent;
    bool processed;
    long long population;
};

int main()
{ 
    long numPeople, numPairs;

    cin >> numPeople >> numPairs;

    vector<CountryNode*> people(numPeople,nullptr );  // Tracks country people belong to. 


    for (long i = 0; i < numPairs; ++i) {
        long a, b;
        cin >> a >> b;

        if ((people[a] == nullptr) && (people[b] == nullptr)) {
            // New country
            //cout << "new " << a << " " << b << endl;
            CountryNode* country = new CountryNode(2);
            people[a]=country;
            people[b]=country;
        } else {
            if ((people[a] != nullptr) && (people[b] != nullptr)) {
                // Countries are being combined. No increase in population
                //cout << "connect " << a << " " << b << endl;
                CountryNode* countryA=people[a];
                while (countryA->parent != nullptr) countryA = countryA->parent;
                CountryNode* countryB=people[b];
                while (countryB->parent != nullptr) countryB = countryB->parent;
                if (countryA != countryB) {
                    //cout << "a is parent of b" << endl;
                    countryA->parent = countryB;
                }
            } else if (people[a] != nullptr) {
                CountryNode* country = people[a];
                people[b]=country;
                country->population++;
                //cout << "add " << b << " to " << a << endl;
            } else if (people[b] != nullptr) {
                CountryNode* country = people[b];
                people[a]=country;
                country->population++;
                //cout << "add " << a << " to " << b << endl;
            } else {
                assert(1);  // should never reach here
            }

        }
    }

    // answer we are looking for
    long long numCombos=0;
    // we will keep reducing pendingPopulation as we process each country
    long long pendingPopulation=numPeople;


    //  find a list of ultimate country nodes
    //  At the same time process people that don't belong to any country
    vector <CountryNode*> rootCountries;
    
    // iterate through people to find single person countries
    //cout << "iterating people " << numPeople << endl;
    for (long i=0; i < numPeople ; i++) {
        if (people[i] == nullptr) {
            //cout << "people " << i << " " << pendingPopulation << " " << numCombos << endl;
            pendingPopulation--;
            numCombos += pendingPopulation;
        } else {
            CountryNode *country = people[i];
            // processed = true for root node if it has been placed in rootCountries
            // processed = true for leafe node if it's population has been added to root country
            if (country->processed == false) {
                country->processed=true;
                if (country->parent == nullptr) {
                    rootCountries.push_back(country);
                } else {
                    CountryNode* root = country;
                    while (root->parent != nullptr) root=root->parent; 
                    root->population += country->population;
                    if (root->processed == false) {
                        rootCountries.push_back(root);
                        root->processed = true;
                    }
                }
            }
        }
    }


    //cout << "iterating country " << endl;
    // Iterate through all countries 
    for (CountryNode* country : rootCountries) {
        //cout << "country " << country->population << " pending " << pendingPopulation << " " << numCombos << endl;
        pendingPopulation -= country->population;
        numCombos += pendingPopulation*country->population;
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
/*
9 8
0 1
2 3
4 5
6 7 
1 2
5 6
0 7
2 6

*/
