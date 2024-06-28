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

TreeNode *insert(TreeNode *root, int key)
{
    if (!root)
        return new TreeNode(key);
    if (key < root->val)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

int findFloor(TreeNode *root, int key)
{
    int floor = -1;
    while (root)
    {
        if (root->val == key)
            return root->val;
        if (root->val > key)
            root = root->left;
        else
        {
            floor = root->val;
            root = root->right;
        }
    }
    return floor;
}

int findCeiling(TreeNode *root, int key)
{
    int ceiling = -1;
    while (root)
    {
        if (root->val == key)
            return root->val;
        if (root->val < key)
            root = root->right;
        else
        {
            ceiling = root->val;
            root = root->left;
        }
    }
    return ceiling;
}

vector<vector<int>> minMaxResult(TreeNode *root, vector<int> &queries)
{
    vector<vector<int>> result;
    for (int query : queries)
    {
        int mini = findFloor(root, query);
        int maxi = findCeiling(root, query);
        result.push_back({mini, maxi});
    }
    return result;
}

int main()
{
    TreeNode *root = nullptr;
    vector<int> keys = {10, 5, 1, 7, 40, 50};
    for (int key : keys)
    {
        root = insert(root, key);
    }

    vector<int> queries = {7, 12, 24};
    vector<vector<int>> result = minMaxResult(root, queries);

    for (auto res : result)
    {
        cout << "[" << res[0] << ", " << res[1] << "]" << endl;
    }

    return 0;
}
