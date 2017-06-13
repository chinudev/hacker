// https://www.hackerrank.com/challenges/kingdom-division

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
#include <math.h>

using namespace std;


// N-ary tree
class Node 
{
public:
    Node(int _index) : index(_index), visited(false) {}

    int index;                // Probably redundant
    vector<Node*> neighbours; // Pointer to all neighbors
    bool visited;
};

class Kingdom
{
public:
    vector<Node> nodeVector;
    vector<bool> visited;
    static const uint64_t MOD = 1000*1000*1000 + 7;

public:
    Kingdom(int numNodes) 
    {
        // Add index 0 as a dummy entry
        for (int i=0; i < numNodes+1; i++) nodeVector.push_back(Node(i));
    }

    void AddEdge(int cityA, int cityB)
    {
        Node* nodeA  = &(nodeVector[cityA]);
        Node* nodeB  = &(nodeVector[cityB]);

        nodeA->neighbours.push_back(nodeB);
        nodeB->neighbours.push_back(nodeA);
    }

    void Print()
    {
        cout << "Kingdom " << endl;
        for (auto& node : nodeVector) {
            cout <<  "** " << node.index << " [";
            for (auto& child : node.neighbours) cout << child->index << ",";
            cout <<  "]" << endl;
        }
    }

    // For test purposes. Reset visit counter for all nodes
    void Reset()
    {
        for (Node& node : nodeVector) node.visited=false;
    }


    // kingdom as this node. 
    // if sameKingdom = false, current node needs to ensure at least one 
    //   of its neighour stays in the same group to avoid war.
    // Return value is a pair of values : 
    //   first = combos assuming this node is same color as parent
    //   second = combos assuming this node is diff color than parent
    //     if this node is different than its parent, it will need 
    //     to keep at least one of its neighbours in same group
    //    Hence it follows that  second <= first
    pair<uint64_t,uint64_t> Divide(Node* node)
    {
        //cout << "**** visiting " << node->index << endl;
        assert(node->visited == false);
        node->visited = true;

        uint64_t first  = 1;      // all possible combos in which neighbours can form groups
        uint64_t allOpposite = 1;   // tracks combos when all neighbours are opposite color

        for (Node* nextNode : node->neighbours) {
            if (nextNode->visited == true) continue;          // ignore parent link 
            
            auto ret = Divide(nextNode); 
            first = (first*(ret.first + ret.second)) % MOD;
            allOpposite =  (allOpposite * ret.second) % MOD;
        }
        uint64_t second = first - allOpposite;
        return pair<uint64_t,uint64_t>(first,second);
    }


    uint64_t Divide(int startCity)
    {
        Node* startNode = &(nodeVector[startCity]);
        auto result = Divide(startNode);
        return (2 * result.second) ;
    }

};

void unitTest() 
{
    Kingdom kingdom(5);

    kingdom.AddEdge(1,2);
    kingdom.AddEdge(1,3);

    cout << kingdom.Divide(1) << endl;
    kingdom.Reset();

    kingdom.AddEdge(3,5);
    kingdom.AddEdge(3,4);

    //kingdom.Print();
    //

    cout << "starting test " << endl;
    cout << kingdom.Divide(1) << endl;
    kingdom.Reset();
    cout << kingdom.Divide(2) << endl;
    kingdom.Reset();
    cout << kingdom.Divide(3) << endl;
}

int main()
{
    //unitTest();

    int numNodes;
    cin >> numNodes;

    Kingdom kingdom(numNodes);


    for (int i=0; i < numNodes-1; i++) {
        int nodeA, nodeB;
        cin >> nodeA >> nodeB;
        kingdom.AddEdge(nodeA,nodeB);
    }

    cout << kingdom.Divide(1) << endl;;
}
