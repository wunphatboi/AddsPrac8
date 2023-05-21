#include <vector>
#include <queue>

int kth_largest(std::vector<int> values, int k) {
    std::priority_queue<int> maxHeap;
    for (int value : values) {
        maxHeap.push(value);
    }
    for (int i = 1; i < k; i++) {
        maxHeap.pop();
    }
    return maxHeap.top();
}