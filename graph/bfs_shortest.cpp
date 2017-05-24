// https://www.hackerrank.com/challenges/bfsshortreach

#include <vector>
#include <queue>
#include <iostream> 
#include <stdio.h>
#include <assert.h>

using namespace std;

// bfs should be called with graph filled in with all edges weights filled out
//  -1 means there is no path. 0 or higher value indicates the cost of the path
// This method will fill in all the new paths discovered for the given source
//
void bfs(vector< vector<int> >& graph, const int sourceIndex) 
{
    // In the grid, each row indicates starting point, col destination
    //  grid[node1][node2] gives cost to go from node1 to node2
    //  row 0 and col 0 are invalid
    
    queue<int> nodeList; // list of nodes to process

    for (int k=1; k<graph.size();k++) {
        if (graph[sourceIndex][k] > 0) {
            nodeList.push(k);
        }
    }

    while (!nodeList.empty()) {
        int currIndex = nodeList.front();
        nodeList.pop();

        // go through edges for this node
        for (int k=1; k<graph.size();k++) {
            if (graph[currIndex][k] > 0) {
                // Process node k only if it is not reachable from source 
                if (graph[sourceIndex][k] < 0) {
                    assert(graph[sourceIndex][currIndex] > 0);
                    graph[sourceIndex][k] = graph[sourceIndex][currIndex] + graph[currIndex][k];
                    nodeList.push(k);
                }
            }
        }
    }

}

void printGraph(vector< vector<int> >& graph)
{
    for (auto row : graph) {
        for (auto cell : row) {
            printf("%4d ",cell);
        }
        cout << endl;
    }
}

int main()
{
    int numQuery;
    cin >> numQuery;

    for (;numQuery>0; numQuery--) {
        int numNodes, numEdges;
        cin >> numNodes >> numEdges;

        // Create a numNodes x numNodes grid filled with -1
        vector<vector<int>> grid(numNodes+1, vector<int>(numNodes+1,-1));
        for (int k=0; k<numNodes;k++) grid[k][k]=0;

        for (;numEdges>0; numEdges--) {
            int node1, node2;
            cin >> node1 >> node2;
            grid[node1][node2] = 6;
            grid[node2][node1] = 6;
        }

        int startIndex;
        cin >> startIndex;

        //printGraph(grid);
        bfs(grid,startIndex);
        //printGraph(grid);
        for (int col=1; col<=numNodes; col++) {
            if (col != startIndex) {
                cout << grid[startIndex][col] << " ";
            }
        }
        cout << endl;
    }

}
