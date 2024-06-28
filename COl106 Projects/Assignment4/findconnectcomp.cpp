#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int node, vector<vector<int>> &adjList, vector<bool> &visited)
{
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int neighbor : adjList[curr])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int countConnectedComponents(int n, vector<vector<int>> &adjList)
{
    vector<bool> visited(n, false);
    int components = 0;

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            bfs(i, adjList, visited);
            components++;
        }
    }

    return components;
}

int main()
{
    // Test cases
    vector<vector<vector<int>>> graphs = {
        {{1}, {0, 2}, {1}, {4}, {3}},                                                                                                   // n = 5
        {{4, 9}, {8, 11, 14}, {6, 13}, {}, {0, 9}, {10, 13}, {2, 10}, {12}, {1, 14}, {0, 4}, {5, 6}, {1, 14}, {7}, {2, 5}, {1, 8, 11}}, // n = 15
        {{1, 2}, {0, 2}, {0, 1, 3}, {2}}                                                                                                // n = 4
    };

    for (int i = 0; i < graphs.size(); ++i)
    {
        int n = graphs[i].size();
        int numComponents = countConnectedComponents(n, graphs[i]);
        cout << "Graph " << (i + 1) << ": Number of connected components = " << numComponents << endl;
    }

    return 0;
}
