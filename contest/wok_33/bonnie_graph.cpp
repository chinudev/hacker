// https://www.hackerrank.com/contests/w33/challenges/bonnie-and-clyde

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <assert.h>

using namespace std;


class AdjList_Graph
{
public:
    int numVertex;
    vector<vector<int>> adjListVector;

    // Store what component a node belongs to. 0 => not valid
    vector<int> componentId;
    int numComponents;

public:
    AdjList_Graph(int numVertex_) :
        numVertex(numVertex_) , 
        adjListVector(numVertex),
        numComponents(0)
    {}

    void AddEdge(int u, int v)
    {
        adjListVector[u].push_back(v);
        adjListVector[v].push_back(u);
    }

    // Find what component each vertex belongs to
    void ComputeConnected()
    {
        // state 0 = not visited 
        //       1 = in stack 
        //       2 = visited
        vector<int> visited(numVertex, 0);

        // We don't allocate memory for componentId vector unless this
        // method is called.
        componentId.resize(numVertex,0);

        // Do a DFS 
        vector<int> idStack;

        int compId = 1;
        for (int i=0; i < numVertex; i++) {
            if (visited[i] == 0) {
                idStack.push_back(i);

                while(!idStack.empty()) {
                    int id = idStack.back();
                    idStack.pop_back();

                    //cout << "   visiting " << id << endl;
                    componentId[id] = compId;
                    visited[id] = 2;

                    for (auto neighbor : adjListVector[id]) {
                        if (visited[neighbor] == 0) {
                            //cout << "   stacking " << neighbor << endl;
                            visited[neighbor] = 1;
                            idStack.push_back(neighbor);
                        }
                    }
                }
                compId++;
            }
        }
        numComponents = compId-1;
    }

    vector<int> biCompId; // stores bi-connected component id
    vector<bool> ap;       // true if vertex is articulation 

    // internal method to recursively compute AP
    void computeAP(int vertexId, 
                   vector<bool>& visited,
                   vector<int>& visitTime,
                   vector<int>& parent,
                   int& time
                   ) 
    {
        int children=0; // only needed for root 

        visited[vertexId] = true;
        time++;
        visitTime[vertexId] = time;
        biCompId[vertexId] = time;

        // go through neighbors; called child here since we are
        //  creating a DFS tree
        for (auto childId : adjListVector[vertexId]) {
            if (visited[childId]) {
                // check if we have looped back and found a second path. 
                if (parent[vertexId] != childId) { // don't check your parent
                    biCompId[vertexId] = min(biCompId[vertexId], visitTime[childId]);
                }
            } else {
                children++;
                parent[childId] = vertexId;
                computeAP(childId, visited, visitTime, parent, time);

                // need to lower biCompId if child found a loop(backpath)
                biCompId[vertexId] = min(biCompId[vertexId], biCompId[childId]);

                // vertexId is an articulation point if visit time of this vertex
                //  is <= the biCompId of any of its children
                // It will be equal if the child looped back onto this vertex.
                // It will be less if child is dangling by one edge connected to this vertex
                if ((parent[vertexId] != -1) && 
                    (visitTime[vertexId] <= biCompId[childId])) {
                    ap[vertexId]=true;
                }
            }
        }
        // if this is the root vertex and it has at least two child, this is
        //   an articulaiton point
        if ((parent[vertexId] == -1) && (children > 1)) {
            ap[vertexId] = true;
        }


    }

    void ComputeArticulated() 
    {
        vector<bool> visited(numVertex, false);
        vector<int> visitTime (numVertex, 0);
        vector<int> parent(numVertex, -1);

        biCompId.resize(numVertex);
        ap.resize(numVertex, false);

        int time=0;
        for (int i=0; i < numVertex; i++) {
            if (visited[i] == false) {
                //cout << " bi comp for id " << i << endl;
                computeAP(i, visited, visitTime, parent, time);
            }
        }
    }

    void Print() {
        cout << "Printing graph properties" << endl;
        for (int i=0; i < numVertex; i++) {
            cout << i << "  ";
            cout << componentId[i] << " ";
            cout << biCompId[i] << " ";
            cout << ap[i] << " ";
            cout << endl;
        }
    }

    // find path using binCompId
    set<int> findPath(int src, int dest) 
    {
        set<int> pathSet;

        vector<bool> visited(numVertex, false);
        vector<int> parent(numVertex, -1);

        // Do a BFS 
        queue<int> idQueue;

        idQueue.push(src);
        int lastId = -1;

        while (!idQueue.empty()) {
            int id = idQueue.front();
            idQueue.pop();

            if (visited[id] == true) continue;
            visited[id] = true;

            // stop if we reach same bi-connected component as dest
            if (biCompId[id] == biCompId[dest]) {
                lastId = id;
                break;
            }

            for (auto neighbor : adjListVector[id]) {
                if (visited[neighbor] == 0) {
                    parent[neighbor] = id;
                    idQueue.push(neighbor);
                }
            }
        }

        if (lastId == -1) return pathSet;

        while (lastId != src) {
            pathSet.insert(lastId);
            lastId = parent[lastId];
        }
        pathSet.insert(src);

        return pathSet;
    }

    // can you go from v1 and v2 to dest without a common node ? 
    bool getAnswer(int v1, int v2, int dest) 
    {
        // Handle edge cases
        if (v1 == v2) {
            if (v1 == dest) return true;
            return false;
        }

        // we can still have v1==dest or v2==dest

        // if the vertex are not even in same component there is no meeting
        if (componentId[v1] != componentId[dest]) return false;
        if (componentId[v2] != componentId[dest]) return false;

        if ((biCompId[v1] == biCompId[dest]) &&
            (biCompId[v2] == biCompId[dest])) {
            return true;
        }

        auto v1Path = findPath(v1, dest);
        auto v2Path = findPath(v2, dest);

        bool overlap = false;
        for (auto entry : v1Path) {
            if (entry == dest) continue;
            if (v2Path.find(entry) != v2Path.end()) {
                overlap = true;
            }
        }

        if (overlap == false) return true;

        // TODO : remove common node and try iteratively to check for 
        //   any other paths 
        //  for now returning false

        return false;


    }
};


void testConnected()
{
    AdjList_Graph graph1(13);

    graph1.ComputeConnected();
    assert( graph1.numComponents == 13);
    assert( graph1.componentId[0] == 1);

    graph1.AddEdge(1,2);
    graph1.AddEdge(2,3);
    graph1.AddEdge(1,3);
    graph1.AddEdge(2,4);

    graph1.AddEdge(5,6);
    graph1.AddEdge(6,7);
    graph1.AddEdge(7,5);
    graph1.AddEdge(7,8);   
    graph1.AddEdge(8,9);   
    graph1.AddEdge(9,10);   
    graph1.AddEdge(10,11);   
    graph1.AddEdge(9,11);   
    graph1.AddEdge(10,12);   

    graph1.ComputeConnected();
    graph1.ComputeArticulated();
    //graph1.Print();

    assert( graph1.numComponents == 3);
    assert( graph1.componentId[1] == graph1.componentId[3]);
    assert( graph1.componentId[5] == graph1.componentId[12]);

    assert( graph1.ap[2] == true); // vertex 2 is an articulation point
    assert( graph1.ap[3] == false);
    assert( graph1.biCompId[3] == graph1.biCompId[2]); 

    assert( graph1.ap[8] == true);
    assert( graph1.ap[9] == true);
    assert( graph1.ap[11] == false);
    assert( graph1.ap[12] == false);

    cout << "testConnected passed" << endl;
}

void test()
{
    testConnected();
}

int main() 
{

    //test();
    int numVertex, numEdges, numQuery;
    cin >> numVertex >> numEdges >> numQuery;

    AdjList_Graph graph(numVertex+1); // 0 is dummy

    for (int i=0; i < numEdges; i++) {
        int a,b;
        cin >> a >> b;
        graph.AddEdge(a,b);
    }

    graph.ComputeConnected();
    graph.ComputeArticulated();
    //graph.Print();


    for (int i=0; i < numQuery; i++) {
        int v1,v2,dest;
        cin >> v1 >> v2 >> dest;
        bool answer = graph.getAnswer(v1,v2,dest);
        if (answer) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

}

