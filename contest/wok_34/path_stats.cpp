
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
    vector<int> parentVector;          // store parent for each node
    vector<uint32_t> valueVector;       // value for each vertex

    vector<int> tempValueVector;       // used for iterations
    const int RootId = 1;

public:
    AdjList_Graph(int numVertex_) :
        numVertex(numVertex_+1) , 
        adjListVector(numVertex+1),
        parentVector(numVertex+1),
        tempValueVector(numVertex+1)
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


    void _compute(int nodeId, int parentId) 
    {
        parentVector[nodeId] = parentId;

        vector<int>& nodeVector = adjListVector[nodeId];

        // Recursively call children
        for (int i=0;i < nodeVector.size(); i++) {
            if (nodeVector[i] != parentId) {
                _compute(nodeVector[i], nodeId);
            }
        }
    }

    // call this after adding all the edges
    void ComputePath() 
    {
        _compute(RootId, -1);
    }

    int FindK_OnPath(int u, int v,int k)
    {
        if (u == v) return valueVector[u];

        unordered_map<int,int> freq;   // key = Ci , value = freq
        int currNode = u; 
        while (currNode != -1) {
            freq[valueVector[currNode]]++;
            //cout << "  u : incr " << currNode << ":" <<  freq[valueVector[currNode]] << endl;
            tempValueVector[currNode]=u;
            currNode = parentVector[currNode];
        }

        currNode = v;
        while (currNode != -1) {
            if (tempValueVector[currNode] == u) {
                currNode = parentVector[currNode];
                break;
            }
            freq[valueVector[currNode]]++;
            //cout << "  v : incr " << currNode << ":" <<  freq[valueVector[currNode]] << endl;
            currNode = parentVector[currNode];
        }

        while (currNode != -1) {
            freq[valueVector[currNode]]--;
            //cout << "  v : decr " << currNode << ":" <<  freq[valueVector[currNode]] << endl;
            currNode = parentVector[currNode];
        }
        
        // store in a vector of pair to sort
        vector<pair<int,int>> orderVector;
        for (auto it=freq.begin(); it != freq.end(); ++it) {
            //cout << "  insert " << it->first << ":" <<  it->second << endl;
            orderVector.emplace_back(it->second, it->first); // put freq as first
        }
        sort(orderVector.rbegin(), orderVector.rend());
        return orderVector[k-1].second;
    }

    void Print() 
    {
        for (int i=0; i < numVertex; i++) {
            cout << i << " : " << valueVector[i] 
                 << " parent(" << parentVector[i] 
                 << ") adj=[";
            for (auto elem: adjListVector[i]) {
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
    cout << tree.FindK_OnPath(1,2,1) << endl;
    cout << tree.FindK_OnPath(1,2,2) << endl;
    cout << tree.FindK_OnPath(1,3,1) << endl;
    cout << tree.FindK_OnPath(1,3,3) << endl;

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

    for (int i=0; i < numQueries; i++) {
        int u,v,k;
        cin >> u >> v >> k;
        cout << tree.FindK_OnPath(u,v,k) << endl;
    }

}

