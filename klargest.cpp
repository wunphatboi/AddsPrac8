#include <vector>
#include <queue>

int kth_largest(std::vector<int> values, int k) {
    // Create a max heap using priority_queue
    std::priority_queue<int> maxHeap;

    // Insert elements from the vector into the max heap
    for (int value : values) {
        maxHeap.push(value);
    }

    // Extract the kth largest element from the max heap
    for (int i = 1; i < k; i++) {
        maxHeap.pop();
    }

    return maxHeap.top();
}