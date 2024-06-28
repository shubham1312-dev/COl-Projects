#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Stable Bucket Sort function
vector<vector<int>> stableBucketSort(vector<vector<int>> &arr)
{
    // Determine the maximum value of the first element in the internal vectors
    int maxValue = 0;
    for (const auto &vec : arr)
    {
        maxValue = max(maxValue, vec[0]);
    }

    // Create buckets based on the maximum value (m is at most max(1000, 3n))
    vector<vector<vector<int>>> buckets(maxValue + 1);

    // Distribute elements into buckets based on the first element of each internal vector
    for (const auto &vec : arr)
    {
        int index = vec[0];
        buckets[index].push_back(vec);
    }

    // Collect elements from buckets back into the original vector in sorted order
    vector<vector<int>> result;
    for (int i = 0; i <= maxValue; ++i)
    {
        for (const auto &vec : buckets[i])
        {
            result.push_back(vec);
        }
    }

    return result;
}

int main()
{
    vector<vector<vector<int>>> testCases = {
        {{2, 4}, {2, 6}, {1, 10}, {1, 5}, {1, 7}},
        {{50, 20}, {10, 30}, {20, 40}, {50, 10}, {10, 20}, {15, 25}}};

    for (int i = 0; i < testCases.size(); ++i)
    {
        vector<vector<int>> sorted = stableBucketSort(testCases[i]);
        cout << "Test Case " << (i + 1) << ": ";
        for (const auto &vec : sorted)
        {
            cout << "[" << vec[0] << "," << vec[1] << "] ";
        }
        cout << endl;
    }

    return 0;
}
