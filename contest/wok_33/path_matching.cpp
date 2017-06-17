// https://www.hackerrank.com/contests/w33/challenges/path-matching

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <assert.h>

using namespace std;


class AdjList_Graph
{
public:
    int numVertex;
    vector<vector<int>> adjListVector;

    int root;
    // Track some information for each node
    vector<int> superParent;
    vector<vector<int>> pathToSuperParent;

    int SegmentDepth;     // TODO tweak for performance

    // String variables
    string& index;         // maps 
    string& pattern;       // pattern we will be looking for

    // Same buffer is used for each query
    char pathStr[200*1000];    // allocate for worst case


public:
    AdjList_Graph(int numVertex_, string& index_, string& pattern_) :
        numVertex(numVertex_) , 
        adjListVector(numVertex),
        root(1),                        // arbitrarily pick 1 as the root
        superParent(numVertex,-1),
        pathToSuperParent(numVertex),
        SegmentDepth(100),
        index(index_),
        pattern(pattern_)
    {}

    void AddEdge(int u, int v)
    {
        adjListVector[u].push_back(v);
        adjListVector[v].push_back(u);
    }


    // keep track of super-parents that need to be processed.
    // using a combination of stack + recursion
    // Recurse until we hit max depth; then declare the nodes super-parents and 
    //  push onto this vector for another round of recursive parsing 
    vector<int> superParentStack; 

    // recursive routine to map out all nodes in this "superParent's" segment
    void processSuperParent(
            int id,       // node being processed
            int superParentId,  // super-parent for this recursive pass
            vector<int>& path,  // path to the super-parent
            int depth           // depth of this node
            ) 
    {
        // Special handling for the first node viz. superParent
        //   could also have done (superParent[id] == -1) 
        if (id != superParentId) {
            superParent[id] = superParentId;
            pathToSuperParent[id] = path;     // should make a copy of the vector
        }

        if (depth < SegmentDepth) {
            // Recurse through children
            path.push_back(id);
            for (auto child: adjListVector[id]) {
                // This check protects against a node visiting its parent
                if (superParent[child] == -1)  {
                    processSuperParent(child, superParentId, path, depth+1);
                }
            }
            path.pop_back();
        } else {
            // Declare this node a super-parent
            superParentStack.push_back(id);
        }
    }

    void ProcessTree() 
    {
        superParent[root]=root;
        superParentStack.push_back(root);
        while(!superParentStack.empty()) {
            int id = superParentStack.back();
            //cout << "Processing super-parent " << id << endl;
            superParentStack.pop_back();
            vector<int> emptyPath;

            processSuperParent(id, id, emptyPath, 0);
        }
    }

    vector<int> getSuperParentPath(int node) 
    {
        vector<int> path;
        return path;
    }

    int getMatch(int src, int dest) 
    {
        return 0;
    }

    void Print() 
    {
        cout << "Printing graph properties" << endl;
        for (int i=1; i < numVertex; i++) {

            cout << i << " " << index[i-1] << " super " << superParent[i];

            cout << "  path : (";
            for (auto node: pathToSuperParent[i]) {
                cout << node << ",";
            }
            cout << ")  " ;

            cout << "  children : (";
            for (auto child: adjListVector[i]) {
                cout << child << ",";
            }
            cout << ")" << endl;
        }
    }
};


void test()
{
    string index = "abbaaabab";
    string pattern = "aba";
    AdjList_Graph graph1(10, index, pattern);

    graph1.AddEdge(1,2);
    graph1.AddEdge(2,4);
    graph1.AddEdge(2,5);
    graph1.AddEdge(1,3);

    graph1.AddEdge(4,6);
    graph1.AddEdge(4,7);
    graph1.AddEdge(5,8);
    graph1.AddEdge(5,9);

    graph1.SegmentDepth = 2;   // set to low value to ease testing
    graph1.ProcessTree();
    graph1.Print();

    cout << "testConnected passed" << endl;
}


int main() 
{

    //test();

    int numNodes, numQuery;
    cin >> numNodes >> numQuery;
    string index;
    string pattern;
    cin >> index;
    cin >> pattern;

    AdjList_Graph graph(numNodes+1, index, pattern);

    for (int i=0; i < numNodes-1; i++) {
        int u, v;
        cin >> u >> v;
        graph.AddEdge(u,v);
    }

    graph.SegmentDepth = 4;   // set to low value to ease testing
    graph.ProcessTree();
    graph.Print();

    for (int i=0; i < numQuery; i++) {
        int u, v;
        cin >> u >> v;
        cout << " path from " << u << " to " << v << " ";
        cout << graph.getMatch(u,v) << endl;
    }

}

