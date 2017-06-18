// https://www.hackerrank.com/contests/w33/challenges/path-matching

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <assert.h>

using namespace std;


class Node
{
public: 
    vector<int> adjList;
};


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
    string& indexStr;         // maps 
    string& patternStr;       // pattern we will be looking for

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
        indexStr(index_),
        patternStr(pattern_)
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

        // Don't do this for super-parent
        //   could also have done (superParent[id] == -1) 
        if (id != superParentId) {
            path.push_back(id);
            superParent[id] = superParentId;
            pathToSuperParent[id] = path;     // make a copy of the vector
        }

        if (depth < SegmentDepth) {
            // Recurse through children
            for (auto child: adjListVector[id]) {
                // This check protects against a node visiting its parent
                if (superParent[child] == -1)  {
                    processSuperParent(child, superParentId, path, depth+1);
                }
            }
        } else {
            // Declare this node a super-parent
            superParentStack.push_back(id);
        }

        if (id != superParentId) {
            path.pop_back();
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

        path.push_back(node);
        while (node != root) {
            node = superParent[node];
            path.push_back(node);
        }
        return path;
    }

    int getMatch(int src, int dest) 
    {
        if (src == dest) {
            if ((patternStr.size() == 1) && (patternStr[0] == indexStr[src-1])) return 1;
            return 0;
        }

        vector<int> srcPath = getSuperParentPath(src);
        vector<int> destPath = getSuperParentPath(dest);

        cout << src << " -> " << dest << endl;

        cout << " src path " << src << ":";
        for (auto elem: srcPath) cout << " " << elem;
        cout << endl;
        cout << " dest path " << dest << ":";
        for (auto elem: destPath) cout << " " << elem;
        cout << endl;

        int commonSuperParent = -1;
        if (src == root || dest == root) {
            commonSuperParent = root;
        } else {
            while (srcPath.back() == destPath.back()) {
                commonSuperParent = srcPath.back();
                srcPath.pop_back();
                destPath.pop_back();
            }
        }
        assert(commonSuperParent != -1);
        //assert(srcPath.size() > 0);
        //assert(destPath.size() > 0);

        cout << " ** common " << commonSuperParent << endl;
        /*
        cout << " *src path " << src << ":";
        for (auto elem: srcPath) cout << " " << elem;
        cout << endl;
        cout << " *dest path " << dest << ":";
        for (auto elem: destPath) cout << " " << elem;
        cout << endl;
        */

        // handle src to common super parent 
        int charIndex=0;
        //int currNode = srcPath[0];
        int currNode = src;
        for (int i=1; i < srcPath.size(); i++) {
            assert(superParent[currNode] == srcPath[i]);

            // need to reverse this as path goes from super-parent to the node
            auto& currPath = pathToSuperParent[currNode];
            for (int k = currPath.size()-1; k >= 0; k--) {
                pathStr[charIndex++] = indexStr[currPath[k]-1];
            }
            currNode = srcPath[i];
        }
        pathStr[charIndex]='\0';
        cout << " path after src = " << pathStr << endl;

        // handle common super-parent 
        //int nextNode = destPath.back();
        int nextNode = dest;
        assert(superParent[currNode] == commonSuperParent);
        assert(superParent[nextNode] == commonSuperParent);

        int commonIndex=0;
        auto currPath = pathToSuperParent[currNode];
        auto nextPath = pathToSuperParent[nextNode];

        while (1) {
            if (currPath.size() == commonIndex) break;
            if (nextPath.size() == commonIndex) break;
            if (currPath[commonIndex] != nextPath[commonIndex]) break;
            commonIndex++;
        }
        commonIndex--;  // commonIndex points to the common node. 
                        // If -1, => super-parent is the common node
 
        cout << " common index " << commonIndex << " for " << currNode << "," << nextNode << endl;

        // copy in reverse order for src side
        for (int i=currPath.size()-1; i > commonIndex; i--) {
            pathStr[charIndex++] = indexStr[currPath[i]-1];
        }

        pathStr[charIndex]='\0';
        cout << " path after common src = " << pathStr << endl;

        if (commonIndex == -1)  {
            pathStr[charIndex++] = indexStr[superParent[currNode]-1];
        } else {
            pathStr[charIndex++] = indexStr[currPath[commonIndex]-1];
        }

        pathStr[charIndex]='\0';
        cout << " path after common middle = " << pathStr << endl;

        for (int i=commonIndex+1; i < nextPath.size(); i++) {
            pathStr[charIndex++] = indexStr[nextPath[i]-1];
        }

        pathStr[charIndex]='\0';
        cout << " path after common dest = " << pathStr << endl;


        // handle common super parent to dest
        //  need to do in reverse order of super-parent path destPath
        for (int i=destPath.size()-2; i >= 0; i--) {
            assert(superParent[destPath[i]] == nextNode);

            nextNode = destPath[i];
            auto& nextPath = pathToSuperParent[nextNode];
            for (int k = 0; k < nextPath.size(); k++) {
                pathStr[charIndex++] = indexStr[nextPath[k]-1];
            }
        }
        pathStr[charIndex] = '\0';

        cout << "string = " << pathStr << endl;

        // handle the common element


        return -1;
    }

    void Print() 
    {
        cout << "Printing graph properties" << endl;
        for (int i=1; i < numVertex; i++) {

            cout << i << " " << indexStr[i-1] << " super " << superParent[i];

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
        int ans = graph.getMatch(u,v);
        cout << "answer = " << ans << endl;
    }

}

