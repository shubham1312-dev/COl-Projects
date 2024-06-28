#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder
{
private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    void addNum(int num)
    {
        if (maxHeap.empty() || num <= maxHeap.top())
        {
            maxHeap.push(num);
        }
        else
        {
            minHeap.push(num);
        }

        if (maxHeap.size() > minHeap.size() + 1)
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    int findMedian()
    {
        if (maxHeap.size() == minHeap.size())
        {
            return (maxHeap.top() + minHeap.top()) / 2;
        }
        else
        {
            return maxHeap.top();
        }
    }
};

int main()
{
    MedianFinder mf;
    vector<int> nums = {31, 15, 13, 18, 84, 12};
    for (int num : nums)
    {
        mf.addNum(num);
        cout << "Current median: " << mf.findMedian() << endl;
    }
    return 0;
}
