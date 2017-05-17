#include <iostream>
#include <vector>

using namespace std;

int circularWalk(int numNodes, int start, int dest, 
                 int r_0, int g, int seed, int p)
{
        if (start == dest) return 0;

        // Fill up the jump table
        vector<int> jumpTable(numNodes);
        int runningValue = r_0;
        for (int i=0;i<numNodes;i++) {
                jumpTable[i] = runningValue;
                runningValue = (runningValue*g + seed) % p;
        }

        vector<int> exploreList;

        exploreList.push_back(start);
        int jumpCount=1;
        while (!exploreList.empty()) {
                vector<int> newExploreList;

                for (int entry : exploreList) {
                        //assert(entry != dest);
                        //cout << "exploring " << entry << endl;
                        int jumpSize = jumpTable[entry];
                        
                        //shouldn't really happen since we never insert such element
                        //  in exploreList
                        if (jumpSize == 0) continue;

                        // shortcut in case we can reach dest 
                        int distToDest=abs(entry-dest);
                        if (distToDest > numNodes/2) {
                                distToDest = numNodes-distToDest;  // wrap around
                        }
                        if (distToDest < jumpSize) return jumpCount;

                        // go through all reachable nodes
                        for (int offset=-jumpSize; offset <= jumpSize; offset++) {
                                if (offset==0) continue;

                                int index = (entry+offset+numNodes) % numNodes;
                        //cout << " looking at index " << index << endl;
                                if (index == dest) return jumpCount;
                                if (jumpTable[index] != 0) {
                                        newExploreList.push_back(index);
                                        //cout << "added " << index << endl;
                                }
                        }
                        // mark this node as explored
                        jumpTable[entry]=0;
                }

                exploreList.swap(newExploreList);
                jumpCount++;
        }


        return -1;

}

int main() 
{
    int n;
    int s;
    int t;
    cin >> n >> s >> t;
    int r_0;
    int g;
    int seed;
    int p;
    cin >> r_0 >> g >> seed >> p;
    int result = circularWalk(n, s, t, r_0, g, seed, p);
    cout << result << endl;
    return 0;
}
