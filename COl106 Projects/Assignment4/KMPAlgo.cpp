#include <iostream>
#include <vector>
using namespace std;

// Function to compute the LPS (Longest Prefix which is also Suffix) array for pattern
vector<int> computeLPS(const string &pattern)
{
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0; // Length of the previous longest prefix suffix

    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[len])
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

// Function to count occurrences of pattern in text using KMP algorithm
int KMPSearch(const string &text, const string &pattern)
{
    int n = text.size();
    int m = pattern.size();

    // Compute LPS array for the pattern
    vector<int> lps = computeLPS(pattern);

    int i = 0;     // index for text[]
    int j = 0;     // index for pattern[]
    int count = 0; // count of occurrences

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }

        if (j == m)
        {
            count++;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return count;
}

int main()
{
    vector<pair<string, string>> testCases = {
        {"AABAACAADAABAABA", "AABA"},
        {"AAAAAAAAAA", "AAA"},
        {"heyhihey", "heyi"}};

    for (int i = 0; i < testCases.size(); ++i)
    {
        string s = testCases[i].first;
        string p = testCases[i].second;
        int occurrences = KMPSearch(s, p);
        cout << "Test Case " << (i + 1) << ": " << occurrences << endl;
    }

    return 0;
}
