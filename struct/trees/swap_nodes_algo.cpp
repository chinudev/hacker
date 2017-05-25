// https://www.hackerrank.com/challenges/swap-nodes-algo

#include <iostream>
#include <vector> 

using namespace std;

class Node 
{
public: 
    Node() : index(-1) , left(nullptr), right(nullptr) {}

    int index;
    Node *left;
    Node *right;

};

void inorderPrint(const Node* root) 
{
    if (root == nullptr) return;
    inorderPrint(root->left);
    cout << root->index << " ";
    inorderPrint(root->right);
}


void swapNodes(Node* root, int k, int currLevel=1)
{
    if (root == nullptr) return;
    //cout << root->index << " at " << currLevel << " with " << k << endl;

    // swap if level is multiple of k
    if (currLevel % k == 0) {
        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;
    }

    swapNodes(root->left, k, currLevel+1);
    swapNodes(root->right, k, currLevel+1);
}


int main() 
{
    int numNodes;
    cin >> numNodes;

    // probably not needed but input may come out of order
    vector<Node> nodeVector(numNodes+1);

    for (int index=1; index <= numNodes; index++) {
        int left,right;
        cin >> left >> right;

        nodeVector[index].index = index;
        if (left > 0)  nodeVector[index].left = &(nodeVector[left]);
        if (right > 0) nodeVector[index].right =&(nodeVector[right]);
    }

    Node* root = &(nodeVector[1]);

    int numOps;
    cin >> numOps;

    for (;numOps > 0; numOps--) {
        int swapLevel;
        cin >> swapLevel;
        swapNodes(root,swapLevel);
        inorderPrint(root);
        cout << endl;
    }


}
