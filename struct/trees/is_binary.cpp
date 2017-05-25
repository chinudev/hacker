// https://www.hackerrank.com/challenges/is-binary-search-tree

#include <iostream>
#include <vector> 

using namespace std;

class Node 
{
public: 
    Node() : data(-1) , left(nullptr), right(nullptr) {}

    int data;
    Node *left;
    Node *right;

};

// Value in this sub-tree should be >= min and <= max
bool checkBST(Node* root, int min=0, int max=0xffff) 
{
   if (root == nullptr) return true;
   if ((root->data < min) || (root->data > max)) return false;
   if (checkBST(root->left, min, root->data-1) && 
       checkBST(root->right, root->data+1, max)){
       return true;
   }
   return false;
     
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

        nodeVector[index].data = index;
        if (left > 0)  nodeVector[index].left = &(nodeVector[left]);
        if (right > 0) nodeVector[index].right =&(nodeVector[right]);
    }

    Node* root = &(nodeVector[1]);

    cout << checkBST(root) << endl;

}
