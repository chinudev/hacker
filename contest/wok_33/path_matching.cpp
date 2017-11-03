// https://www.hackerrank.com/contests/w33/challenges/path-matching

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <assert.h>

using namespace std;


int match(char* str, int len, string& pattern) 
{
    int matchCount=0;
    int maxIndex = len - pattern.size();
    for (int i=0; i <= maxIndex; i++) {
        bool match=true;
        for (int k=0; k < pattern.size(); k++) {
            if (str[i+k] != pattern[k]) {
                match=false;
                break;
            }
        }
        if (match) matchCount++;
    }
    return matchCount;
}

class Node
{
public: 
    Node() : superParent(-1) {}

    vector<int> adjList;
    int superParent;
    vector<int> pathFromSuperParent;  // doesn't include super-parent but includes this node

    string fwdPath;    // string version of path above 
    string revPath;    // reverse of the string
};


class AdjList_Graph
{
public:
    int numVertex;
    vector<Node> vertexList;

    int root;
    int SegmentDepth;     // TODO tweak for performance

    // String variables
    string& indexStr;         // maps 
    string& patternStr;       // pattern we will be looking for

    // Same buffer is used for each query
    char pathStr[200*1000];    // allocate for worst case


public:
    AdjList_Graph(int numVertex_, string& index_, string& pattern_) :
        numVertex(numVertex_) , 
        vertexList(numVertex),
        root(1),                        // arbitrarily pick 1 as the root
        SegmentDepth(100),
        indexStr(index_),
        patternStr(pattern_)
    {}

    void AddEdge(int u, int v)
    {
        vertexList[u].adjList.push_back(v);
        vertexList[v].adjList.push_back(u);
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

            Node& idNode = vertexList[id];

            idNode.superParent = superParentId;
            idNode.pathFromSuperParent = path;     // make a copy of the vector

            char charIndex=0;
            for (int elem : path) pathStr[charIndex++] = indexStr[elem-1];
            pathStr[charIndex]='\0';
            idNode.fwdPath = string(pathStr);
            idNode.revPath = idNode.fwdPath;
            reverse(idNode.revPath.begin(),idNode.revPath.end());
        }

        if (depth < SegmentDepth) {
            // Recurse through children
            for (auto child: vertexList[id].adjList) {
                // This check protects against a node visiting its parent
                if (vertexList[child].superParent == -1)  {
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
        vertexList[root].superParent = root;
        superParentStack.push_back(root);
        while(!superParentStack.empty()) {
            int id = superParentStack.back();
            superParentStack.pop_back();
            vector<int> emptyPath;

            //cout << "Processing super-parent " << id << endl;
            processSuperParent(id, id, emptyPath, 0);
        }
    }

    vector<int> getSuperParentPath(int node) 
    {
        vector<int> path;

        path.push_back(node);
        while (node != root) {
            node = vertexList[node].superParent;
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


        vector<int> srcSuperPath = getSuperParentPath(src);
        vector<int> destSuperPath = getSuperParentPath(dest);

        //cout << src << " -> " << dest << " =  ";

        int commonSuperParent = -1;
        /*if (src == root || dest == root) {
            commonSuperParent = root;
        } else */
        {
            while (srcSuperPath.back() == destSuperPath.back()) {
                commonSuperParent = srcSuperPath.back();
                srcSuperPath.pop_back();
                destSuperPath.pop_back();
            }
        }
        assert(commonSuperParent != -1);
        //assert(srcPath.size() > 0);
        //assert(destPath.size() > 0);

        //cout << " ** common " << commonSuperParent << " src " << srcSuperPath.size() << " dest " << destSuperPath.size() << endl;

        int charIndex=0;

        // Go from src node to the common super parent
        int fwdId = src;

        for (int i=1; i < srcSuperPath.size(); i++) {
            Node& fwdNode = vertexList[fwdId];
            assert(fwdNode.superParent == srcSuperPath[i]);

            for (char c : fwdNode.revPath) pathStr[charIndex++] = c;
            fwdId = srcSuperPath[i];
        }
        pathStr[charIndex]='\0';
        //cout << " ** path after src = " << pathStr << endl;


        // handle common super-parent 
        int nextId = dest;
        if (destSuperPath.size() > 0) nextId = destSuperPath.back();

        //cout << " ** handle common = " << fwdId << "." << nextId << endl;

        {
            Node& fwdNode = vertexList[fwdId];
            Node& nextNode = vertexList[nextId];

            if (fwdNode.superParent == nextNode.superParent) {
                auto fwdPath = fwdNode.pathFromSuperParent;
                auto nextPath = nextNode.pathFromSuperParent;
                int commonIndex = 0;

                while (1) {
                    if (fwdPath.size() == commonIndex) break;
                    if (nextPath.size() == commonIndex) break;
                    if (fwdPath[commonIndex] != nextPath[commonIndex]) break;
                    commonIndex++;
                }
                commonIndex--;  // commonIndex points to the common node. 
                                // If -1, => super-parent is the common node
                //cout << " ** common index " << commonIndex << endl;

                for (int i=fwdNode.fwdPath.size()-1; i > commonIndex; i--)  
                    pathStr[charIndex++] = fwdNode.fwdPath[i];

                if (commonIndex == -1)  pathStr[charIndex++] = indexStr[commonSuperParent-1];
                else  pathStr[charIndex++] = fwdNode.fwdPath[commonIndex];

                for (int i=commonIndex+1; i < nextNode.fwdPath.size(); i++) {
                    pathStr[charIndex++] = nextNode.fwdPath[i];
                }

            } else {
                // one must be the  super parent of the other 
                if (fwdId == nextNode.superParent) {
                    pathStr[charIndex++] = indexStr[fwdId-1];
                    for (char c : nextNode.fwdPath) pathStr[charIndex++] = c;
                } else if (fwdNode.superParent == nextId) {
                    for (char c : fwdNode.revPath) pathStr[charIndex++] = c;
                    pathStr[charIndex++] = indexStr[nextId-1];
                } else {
                    assert(false);
                }
            }
        }

        pathStr[charIndex]='\0';
        //cout << " ** path after common= " << pathStr << endl;

        // handle common super parent to dest
        // 

        // use nextId instead of fwdId here.
        for (int i=destSuperPath.size()-2; i >=0; i--) {
            int id = destSuperPath[i];
            //cout << " == dest processing " << i << " id " << id << " next" << nextId << endl;
            Node& idNode = vertexList[id];
            assert(idNode.superParent == nextId);

            for (char c : idNode.fwdPath) pathStr[charIndex++] = c;
            nextId = id;
        }
        pathStr[charIndex]='\0';
        //cout << " ** match string = " << pathStr << endl;

        return match(pathStr, charIndex, patternStr);



        return -1;
    }

    void Print() 
    {
        cout << "Printing graph properties" << endl;
        for (int i=1; i < numVertex; i++) {
            Node& node = vertexList[i];

            cout << i << " " << indexStr[i-1] << " super " << node.superParent;

            cout << "  path : (";
            for (auto node: node.pathFromSuperParent) {
                cout << node << ",";
            }
            cout << ")  " ;

            cout << node.fwdPath << " " << node.revPath;

            cout << " superPath : (";
            for (auto node : getSuperParentPath(i)) cout << node << ",";
            cout << ")";
            /*
            cout << "  children : (";
            for (auto child: node.adjList) {
                cout << child << ",";
            }
            cout << ")";
            */
            cout << endl;
        }
    }
};


/*
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


void test2()
{
    assert(1 ==  match("abcd",4,string("a")));
    assert(1 ==  match("abcd",4,string("abcd")));
    assert(0 ==  match("abcd",4,string("abcde")));
    assert(0 ==  match("abcd",4,string("x")));
    assert(1 ==  match("x",1,string("x")));
    assert(2 ==  match("xyx",3,string("x")));
    assert(4 ==  match("abaaabaaa",9,string("aa")));
}

*/

int main() 
{

    //test();
    //test2();

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

    graph.SegmentDepth = 100;   // set to low value to ease testing
    graph.ProcessTree();
    //graph.Print();

    for (int i=0; i < numQuery; i++) {
        int u, v;
        cin >> u >> v;
        int ans = graph.getMatch(u,v);
        cout << ans << endl;
    }

}

