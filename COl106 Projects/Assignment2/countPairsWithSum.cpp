#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int countPairsWithSum(vector<int> &nums, int target)
{
    unordered_map<int, int> freq;
    int count = 0;
    const int MOD = 1000000007;

    for (int num : nums)
    {
        int complement = target - num;
        if (freq[complement] > 0)
        {
            count = (count + freq[complement]) % MOD;
        }
        freq[num]++;
    }
    return count;
}

int main()
{
    vector<int> nums = {2, 4, 1, 3, 5, 5, 4, 2, 3, 5};
    int target = 6;
    cout << "Number of pairs: " << countPairsWithSum(nums, target) << endl;
    return 0;
}
