#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sortHeightWeight(vector<int> &H, vector<int> &W)
{
    vector<pair<int, int>> people;
    for (size_t i = 0; i < H.size(); ++i)
    {
        people.push_back({H[i], W[i]});
    }

    sort(people.begin(), people.end());

    for (size_t i = 0; i < people.size(); ++i)
    {
        H[i] = people[i].first;
        W[i] = people[i].second;
    }
}

int main()
{
    vector<int> H = {3, 4, 1, 7, 8, 4};
    vector<int> W = {2, 5, 6, 3, 7, 1};

    sortHeightWeight(H, W);

    cout << "Sorted Heights: ";
    for (int h : H)
    {
        cout << h << " ";
    }
    cout << endl;

    cout << "Sorted Weights: ";
    for (int w : W)
    {
        cout << w << " ";
    }
    cout << endl;

    return 0;
}
