
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <stdint.h>

using namespace std;


const uint32_t MOD = 1000*1000*1000 + 7;

class Fibo 
{
public:
    vector<uint32_t> Fib;
    int Max;

public:
    Fibo(int max) : Fib(max), Max(max)
    {
        init();
    }

    void init() 
    {
        int i0=1; Fib[0]=i0;
        int i1=1; Fib[1]=i1;

        for (int i=2; i <= Max; i++) {
            uint32_t newValue = (i0+i1) % MOD;
            Fib[i] = newValue;
            i0=i1;
            i1=newValue;
        }
    }
    
    uint32_t GetValue(int index) 
    {
        assert(index <= Max);
        return Fib[index];
    }
};


class AdjList_Graph
{
public:
    int numVertex;
    vector<vector<int>> adjListVector;
    vector<uint32_t> valueVector;
    Fibo& fib;

    vector<bool> visited;  // used for traversals

public:
    AdjList_Graph(int numVertex_, Fibo& fib_) :
        numVertex(numVertex_) , 
        adjListVector(numVertex),
        fib(fib_),
        visited(numVertex)
    {}

    void AddEdge(int u, int v)
    {
        adjListVector[u].push_back(v);
        adjListVector[v].push_back(u);
    }

    void AddValue(uint32_t value) 
    {
        valueVector.push_back(value);
    }

    void Print() 
    {
        for (int i=0; i < numVertex; i++) {
            cout << i << " : " << valueVector[i] << " [";
            for (auto elem: adjListVector[i]) {
                cout << elem << ",";
            }
            cout << "]" << endl;
        }
    }


    // return sum
    uint32_t VisitNode(
            const int vertexId,            // Tree node to process
            vector<uint32_t>& pathSums,    // insert paths for this child's descendant in vector
            uint32_t& nextIndex)                //  starting at nextIndex. 
    {
        uint32_t sum=0;
        uint32_t vertexValue = valueVector[vertexId];
        const uint32_t startIndex = nextIndex; // remember start index 

        //cout << "Entering " << vertexId << ":" << nextIndex << endl;


        // handle path with this vertex as src and dest
        sum = (sum + fib.GetValue(vertexValue)) % MOD;
        pathSums[nextIndex++] = vertexValue;
        visited[vertexId] = true;


        for (auto childVertex: adjListVector[vertexId]) {
            if (visited[childVertex]) continue;

            //cout << vertexId << "   Handling child " << childVertex << endl;
            uint32_t childIndex = nextIndex;
            sum = (sum + VisitNode(childVertex, pathSums, childIndex)) % MOD;

            for (int uIdx = nextIndex; uIdx < childIndex; uIdx++) {
                // handle path from descendants of this child to :  
                //   1. currentVertex
                //   2. descendants of other childs processed so far
                for (int vIdx = startIndex; vIdx < nextIndex; vIdx++) {
                    sum = (sum + 2*fib.GetValue(pathSums[uIdx]+pathSums[vIdx])) % MOD;
                    //cout << vertexId << "       added path child-child " << sum << endl;
                }

            }

            for (int uIdx = nextIndex; uIdx < childIndex; uIdx++) {
                pathSums[uIdx] += vertexValue;
            }
            nextIndex = childIndex;
        }

        //cout << "Returning from " << vertexId << ":" << sum << ":" << nextIndex << " @";
        //for (int i=0; i < nextIndex;  i++) cout << pathSums[i] << ",";
        //cout << endl;
        return sum;
    }

    void resetVisited() {
        for (int i=0; i < numVertex; i++) visited[i] = false;
    }

    uint32_t GetSum() 
    {
        resetVisited();
        vector<uint32_t> pathSums(numVertex+1); 
        uint32_t nextIndex=0;
        return VisitNode(1, pathSums, nextIndex);
    }

};


void testFib() 
{
    Fibo fib(5*1000*1000);
    //Fibo fib(25);
    for (int i=0; i <10; i++) {
        cout << i << "=" << fib.GetValue(i) << endl;
    }
}

void test1()
{
    Fibo fib(5*1000*1000);
    AdjList_Graph tree(4, fib);

    tree.AddEdge(1,2);
    tree.AddEdge(1,3);

    tree.AddValue(0);
    tree.AddValue(2);
    tree.AddValue(1);
    tree.AddValue(1);

    cout << tree.GetSum() << endl;
}

void test2()
{
    Fibo fib(1000);
    AdjList_Graph tree(12, fib);

    tree.AddEdge(1,2);
        tree.AddEdge(2,5);
        tree.AddEdge(2,6);
        tree.AddEdge(2,7);
    tree.AddEdge(1,3);
        tree.AddEdge(3,8);
        tree.AddEdge(3,9);
    tree.AddEdge(1,4);
        tree.AddEdge(4,10);
        tree.AddEdge(4,11);

    tree.AddValue(0);
    tree.AddValue(1);
    tree.AddValue(3);
    tree.AddValue(1);
    tree.AddValue(2);
    tree.AddValue(0);
    tree.AddValue(1);
    tree.AddValue(2);
    tree.AddValue(1);
    tree.AddValue(2);
    tree.AddValue(1);
    tree.AddValue(2);

    //tree.Print();
    //cout << tree.GetSum() << endl;

    uint32_t sum;
    //sum=0; tree.VisitNode(5,sum); cout << "5 = " << sum << endl;

    tree.resetVisited(); 
    sum=0; tree.visited[1] = true;
    vector<uint32_t> pathSum(10);
    uint32_t nextIndex=0;
    cout << "3 = " << tree.VisitNode(3,pathSum,nextIndex) << endl; 
    for (int i=0; i < nextIndex; i++) cout << pathSum[nextIndex] << ",";
    cout << endl;

}

void test()
{
    //testFib();
    test1();
}

int main() 
{

    //test2();

    int numNodes; 
    cin >> numNodes;

    Fibo fib(25*1000*1000);
    AdjList_Graph tree(numNodes+1, fib);
    
    for (int i=1; i < numNodes; i++) {
        int a,b;
        cin >> a >> b;
        tree.AddEdge(a,b);
    }
    tree.AddValue(0); // value for dummy node #0
    for (int i=0; i < numNodes; i++) {
        int value;
        cin >> value;
        tree.AddValue(value);
    }

    cout << tree.GetSum() << endl;

}

