#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


int main(){
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int numVertex;
        int numEdges;
        int libCost;
        int roadCost;
        cin >> numVertex >> numEdges >> libCost >> roadCost;

        // Adjacency list for each vertex 
        vector< vector<int>> cityRoads(numVertex+1);

        for(int a1 = 0; a1 < numEdges; a1++) {
            int city_1;
            int city_2;
            cin >> city_1 >> city_2;
            cityRoads[city_1].push_back(city_2);
            cityRoads[city_2].push_back(city_1);
        }

        // citySegment tracks segment a city belongs to. 
        //  Initially a city belongs to no segment, indicated by 0
        vector <int> citySegment(numVertex+1,0); 
        int currentSegment=0;

        // This list will keep track of cities we need to visit
        //  in current segment

        vector <int> citiesToVisit;  // empty to start

        for (int startCity=1; startCity <= numVertex; startCity++) {

                if (citySegment[startCity] != 0) continue;

                // Start a new segment
                currentSegment++;
                citiesToVisit.push_back(startCity);

                while (!citiesToVisit.empty()) {
                        int currCity=citiesToVisit.back();
                        citiesToVisit.pop_back();

                        // skip if this city has already been visited
                        if (citySegment[currCity] != 0) continue;

                        // add all edges of currCity to visit list
                        for (int targetCity : cityRoads[currCity]) {
                                if (citySegment[targetCity] == 0) {
                                        citiesToVisit.push_back(targetCity);
                                }
                        }
                        citySegment[currCity] = currentSegment;
                }
        }

        // if libray cost less than road, make a library in every city
        // else make a library in each segment. 
        //  Number of roads = vertex - number_of_segment 
        if (libCost < roadCost) {
                cout << libCost*numVertex << endl;
        } else {
                // number of segment = currentSegment
                int cost = libCost*currentSegment; 
                cost += roadCost*(numVertex - currentSegment);

                cout << cost << endl;
        }


    }
    return 0;
}

