
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <stdint.h>

using namespace std;



class AdjList_Graph
{
public:
    int numVertex;

    vector<vector<int>> adjListVector;
    vector<vector<int>> pathVector;     // path for each vertex
    vector<uint32_t> valueVector;       // value for each vertex
    const int RootId = 1;

public:
    AdjList_Graph(int numVertex_) :
        numVertex(numVertex_+1) , 
        adjListVector(numVertex+1),
        pathVector(numVertex+1)
    {
        valueVector.push_back(0); //dummy value for node 0
    }

    void AddEdge(int u, int v)
    {
        adjListVector[u].push_back(v);
        adjListVector[v].push_back(u);
    }

    void AddValue(uint32_t value) 
    {
        valueVector.push_back(value);
    }


    void _compute(int nodeId, int parentId, vector<int> path) 
    {
        path.push_back(nodeId);
        pathVector[nodeId] = path;

        vector<int>& nodeVector = adjListVector[nodeId];

        // Recursively call children
        for (int i=0;i < nodeVector.size(); i++) {
            if (nodeVector[i] != parentId) {
                _compute(nodeVector[i], nodeId, path);
            }
        }
    }

    // call this after adding all the edges
    void ComputePath() 
    {
        vector<int> dummy;
        _compute(RootId, -1, dummy);
    }

    int FindK_OnPath(int u, int v,int k)
    {
        return -1;
    }

    void Print() 
    {
        for (int i=0; i < numVertex; i++) {
            cout << i << " : " << valueVector[i] << " adj=[";
            for (auto elem: adjListVector[i]) {
                cout << elem << ",";
            }
            cout << "] path=[";
            for (auto elem: pathVector[i]) {
                cout << elem << ",";
            }
            cout << "]" << endl;
        }
    }

};



void test1()
{
    AdjList_Graph tree(6);

    tree.AddEdge(1,4);
    tree.AddEdge(4,5);
    tree.AddEdge(6,2);
    tree.AddEdge(3,6);
    tree.AddEdge(4,2);

    tree.AddValue(1);
    tree.AddValue(1);
    tree.AddValue(3);
    tree.AddValue(2);
    tree.AddValue(4);
    tree.AddValue(2);

    tree.ComputePath(); 

    tree.Print();

}



int main() 
{

    //test1();

    int numNodes, numQueries; 
    cin >> numNodes >> numQueries;

    AdjList_Graph tree(numNodes);
    
    // get values
    for (int i=0; i < numNodes; i++) {
        int value;
        cin >> value;
        tree.AddValue(value);
    }

    // get edges
    for (int i=1; i < numNodes; i++) {
        int a,b;
        cin >> a >> b;
        tree.AddEdge(a,b);
    }

    tree.ComputePath(); 
    //tree.Print();

    for (int i=1; i < numNodes; i++) {
        int u,v,k;
        cin >> u >> v >> k;
        cout << tree.FindK_OnPath(u,v,k) << endl;
    }

}

