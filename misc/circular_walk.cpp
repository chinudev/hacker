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


        // exploreList keeps track of nodes to be explored 
        vector<int> exploreList;
        exploreList.push_back(start);

        int jumpCount=1;
        while (!exploreList.empty()) {

                // newExploreList collects nodes for next round
                vector<int> newExploreList;

                for (int entry : exploreList) {
                        //assert(entry != dest);
                        //cout << "exploring " << entry << endl;
                        int jumpSize = jumpTable[entry];
                        
                        //shouldn't really happen since we never insert such element
                        //  in exploreList
                        if (jumpSize == 0) continue;


                        // check each node for dest and find the node
                        //  that can go the farthest 
                        
                        // We will use this to track best candidate for next round
                        int leftMaxJump  = jumpSize; int leftMaxJumpNode  = entry;
                        int rightMaxJump = jumpSize; int rightMaxJumpNode = entry;

                        for (int offset=1; offset <= jumpSize; offset++) {

                                int rightIndex = (entry+offset+numNodes) % numNodes;
                                if (rightIndex == dest) return jumpCount;
                                int rightJump = offset+jumpTable[rightIndex];
                                if (rightJump > rightMaxJump) {
                                        rightMaxJump=rightJump;
                                        rightMaxJumpNode = rightIndex;
                                }
                                
                                int leftIndex = (entry-offset+numNodes) % numNodes;
                                if (leftIndex == dest) return jumpCount;
                                int leftJump = offset+jumpTable[leftIndex];
                                if (leftJump > leftMaxJump) {
                                        leftMaxJump=leftJump;
                                        leftMaxJumpNode = leftIndex;
                                }

                        }

                        // we won't be exploring these nodes 
                        for (int offset=1; offset <= jumpSize; offset++) {
                                int leftIndex = (entry-offset+numNodes) % numNodes;
                                if (leftIndex != leftMaxJumpNode) jumpTable[leftIndex]=0;
                                int rightIndex = (entry+offset+numNodes) % numNodes;
                                if (rightIndex != rightMaxJumpNode) jumpTable[rightIndex]=0;
                        }
                        jumpTable[entry]=0;


                        // Did we find an entry to explore for next round ? 
                        if (leftMaxJumpNode != entry) {
                                newExploreList.push_back(leftMaxJumpNode);
                        }
                        if (rightMaxJumpNode != entry) {
                                newExploreList.push_back(rightMaxJumpNode);
                        }
                       
                }

                // prepare for next round
                exploreList.swap(newExploreList);
                jumpCount++;
        }

        // unable to reach dest
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
