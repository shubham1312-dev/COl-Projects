#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find the longest common prefix between two strings
string findLCP(const string &str1, const string &str2)
{
    int minLength = min(str1.length(), str2.length());
    int i = 0;
    while (i < minLength && str1[i] == str2[i])
    {
        i++;
    }
    return str1.substr(0, i);
}

// Function to find the longest common prefix among an array of strings
string longestCommonPrefix(vector<string> &strs)
{
    if (strs.empty())
        return "";

    string prefix = strs[0];
    for (int i = 1; i < strs.size(); ++i)
    {
        prefix = findLCP(prefix, strs[i]);
        if (prefix.empty())
            break; // No common prefix found
    }
    return prefix;
}

int main()
{
    vector<vector<string>> testCases = {
        {"abcdefgh", "abcefgh"},
        {"abcdefgh", "aefghijk", "abcefgh"},
        {"sadadadaghjt", "sadadadaghjt", "sadadaghjt", "sadadadadadadaghjt"}};

    for (int i = 0; i < testCases.size(); ++i)
    {
        string result = longestCommonPrefix(testCases[i]);
        cout << "Test Case " << (i + 1) << ": " << result << endl;
    }

    return 0;
}
