#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node *invertTree(Node *root)
{
    if (root == nullptr)
        return root;

    Node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invertTree(root->left);
    invertTree(root->right);

    return root;
}

void preOrder(Node *root)
{
    if (root != nullptr)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Original tree: ";
    preOrder(root);
    cout << endl;

    root = invertTree(root);

    cout << "Inverted tree: ";
    preOrder(root);
    cout << endl;

    return 0;
}
