#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int maxDepth(TreeNode *root)
{
    if (!root)
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

TreeNode *deepestSubtree(TreeNode *root, int depth, int maxDepth)
{
    if (!root)
        return nullptr;
    if (depth == maxDepth)
        return root;

    TreeNode *left = deepestSubtree(root->left, depth + 1, maxDepth);
    TreeNode *right = deepestSubtree(root->right, depth + 1, maxDepth);

    if (left && right)
        return root;
    return left ? left : right;
}

TreeNode *subtreeWithAllDeepest(TreeNode *root)
{
    int maxD = maxDepth(root);
    return deepestSubtree(root, 1, maxD);
}

int main()
{
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode *result = subtreeWithAllDeepest(root);
    cout << "The value of the smallest subtree with all deepest nodes is: " << result->val << endl;
    return 0;
}
