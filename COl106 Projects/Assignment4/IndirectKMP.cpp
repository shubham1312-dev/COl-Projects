#include <iostream>
#include <vector>
using namespace std;

// Function to compute the LPS (Longest Prefix which is also Suffix) array for a given string
vector<int> computeLPS(const string &s)
{
    int n = s.size();
    vector<int> lps(n, 0);
    int len = 0; // length of the previous longest prefix suffix

    int i = 1;
    while (i < n)
    {
        if (s[i] == s[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Function to find the minimum number of characters needed to make the string a palindrome
int minAdditionsToPalindrome(const string &s)
{
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());

    // Create the new string for KMP algorithm
    string combined = s + "#" + rev_s;
    int n = combined.size();

    // Compute LPS array for combined string
    vector<int> lps = computeLPS(combined);

    // The minimum number of additions needed
    return s.size() - lps[n - 1];
}

int main()
{
    vector<string> testCases = {
        "aacecaaa",
        "abcd",
        "aaaaaaa"};

    for (const auto &s : testCases)
    {
        int additions = minAdditionsToPalindrome(s);
        cout << "For \"" << s << "\": " << additions << endl;
    }

    return 0;
}
