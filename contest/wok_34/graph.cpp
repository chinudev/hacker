
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

    vector<uint32_t> VisitNode(int vertexId, uint32_t& sum)
    {
        vector<uint32_t> pathSums;
        uint32_t vertexValue = valueVector[vertexId];
        //cout << "Entering " << vertexId << ":" << sum << endl;

        // handle path with this vertex as src and dest
        sum = (sum + fib.GetValue(vertexValue)) % MOD;
        pathSums.push_back(vertexValue);

        visited[vertexId] = true;

        for (auto childVertex: adjListVector[vertexId]) {
            if (visited[childVertex]) continue;

            //cout << vertexId << "   Handling child " << childVertex << endl;
            vector<uint32_t> childSum = VisitNode(childVertex,sum);
            for (auto value1: childSum) {

                // handle path from descendants of this child to :  
                //   1. currentVertex
                //   2. descendants of other childs processed so far
                for (auto value2: pathSums) {
                    sum = (sum + 2*fib.GetValue(value1+value2)) % MOD;
                    //cout << vertexId << "       added path child-child " << sum << endl;
                }
            }
            // add to the cummulative list of paths from all descendants
            for (auto value1: childSum) pathSums.push_back(value1+vertexValue);
        }

        //cout << "Returning from " << vertexId << ":" << sum << endl;
        return pathSums;
    }

    void resetVisited() {
        for (int i=0; i < numVertex; i++) visited[i] = false;
    }

    uint32_t GetSum() 
    {
        resetVisited();
        uint32_t sum=0;
        VisitNode(1,sum);
        return sum;
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
    Fibo fib(100);
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
    cout << tree.GetSum() << endl;

    uint32_t sum;
    //sum=0; tree.VisitNode(5,sum); cout << "5 = " << sum << endl;

    tree.resetVisited(); 
    sum=0; tree.visited[1] = true;
    vector<uint32_t> pathSum = tree.VisitNode(3,sum); 
    cout << "3 = " << sum << " : ";
    for (auto elem: pathSum) cout << elem << ",";
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

    Fibo fib(5*1000*1000);
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

