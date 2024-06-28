#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minOperationsToMakeSimilar(vector<int> &A, vector<int> &Target)
{
    sort(A.begin(), A.end());
    sort(Target.begin(), Target.end());

    int operations = 0;
    for (size_t i = 0; i < A.size(); ++i)
    {
        operations += abs(A[i] - Target[i]);
    }

    return operations;
}

int main()
{
    vector<int> A = {1, 2, 5};
    vector<int> Target = {4, 1, 3};

    int result = minOperationsToMakeSimilar(A, Target);
    cout << "Minimum operations: " << result << endl;

    return 0;
}
