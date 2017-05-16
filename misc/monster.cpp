// https://www.hackerrank.com/contests/w32/challenges/fight-the-monsters

#include <vector> 
#include <map>
#include <iostream>

using namespace std;


long findKills(long hitPointPerShot, long numShots, vector<long> monsters)
{
        // This array will track how many monsters can be killed by 
        //  given number of shots. 
        map<long, long> hitMap;

        for (long monsterHitPoints : monsters) { 
                
                long numHitsForMonster = int(monsterHitPoints / hitPointPerShot);
                if (monsterHitPoints % hitPointPerShot != 0) numHitsForMonster++;
                //cout << "hit point="<< monsterHitPoints << " shots " << numHitsForMonster << endl;
                if (hitMap.count(numHitsForMonster) > 0) {
                        // increment existing entry
                        hitMap[numHitsForMonster]++;
                } else {
                        // create a new entry
                        hitMap[numHitsForMonster]=1;
                }
        }

        long numKills=0;
        for (auto iter=hitMap.begin(); iter != hitMap.end(); iter++ ) {
                //cout << "category : " << iter->first << " count " << iter->second << endl;
                long maxShots = iter->first * iter->second;

                if (numShots <= maxShots) {
                        long actualKills = long(numShots / iter->first);
                        numKills += actualKills;
                        break;
                } else {
                        numShots -= maxShots;
                        numKills += iter->second;
                }
        }
        return numKills;
}

int main() 
{
        vector<long> monsters = {16,19,7,11,23,8,16};
        cout << findKills(8,6,monsters) << endl;

        cout << findKills(1,6,{100,6,102} ) << endl;

}

