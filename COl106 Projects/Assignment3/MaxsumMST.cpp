#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int key;
    vector<Node *> children;

    Node(int k) : key(k) {}
};

int getMaxMSTHelper(Node *node, int &maxSum)
{
    if (!node)
        return 0;

    int currentSum = node->key;
    bool isValidMST = true;

    for (Node *child : node->children)
    {
        int childSum = getMaxMSTHelper(child, maxSum);
        if (child->key < node->key)
        {
            isValidMST = false;
        }
        currentSum += childSum;
    }

    if (isValidMST)
    {
        maxSum = max(maxSum, currentSum);
    }

    return currentSum;
}

int getMaxMST(Node *root)
{
    int maxSum = 0;
    getMaxMSTHelper(root, maxSum);
    return maxSum;
}

int main()
{
    Node *root = new Node(15);
    root->children.push_back(new Node(10));
    root->children.push_back(new Node(20));
    root->children[0]->children.push_back(new Node(5));
    root->children[0]->children.push_back(new Node(12));
    root->children[1]->children.push_back(new Node(18));
    root->children[1]->children.push_back(new Node(25));

    cout << "Max MST sum: " << getMaxMST(root) << endl;

    return 0;
}
