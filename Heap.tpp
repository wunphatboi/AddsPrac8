#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <cmath> // for floor()

template <typename T>
class Heap {
 private:
  std::vector<T> values;
  void heapify(int);

 public:
  Heap();  // constructs an empty heap

  // constructs a heap with the values from the given vector
  // the type T MUST provide comparison operators <, >, ==
  Heap(std::vector<T>);

  void insert(T);
  void remove(T);
  T getMin();
};

/*******************************/
// default constructor
/*******************************/

template <typename T>
Heap<T>::Heap() {}

/*******************************/
// constructs a heap with the values in the given vector
// the type T MUST provide comparison operators <, >, ==
/*******************************/

template <typename T>
Heap<T>::Heap(std::vector<T> start_values) {
  // copy the values into our heap vector
  for (int i = 0; i < start_values.size(); i++) {
    values.push_back(start_values.at(i));
  }

  // starting from last non-leaf node (last parent), heapify each
  // of the parents
  int initial_parent_index = floor((values.size()-1) / 2);
  for (int parent_index = initial_parent_index; parent_index >= 0;
       parent_index--) {
    heapify(parent_index);
  }
}

/*******************************/
// add values to the heap
/*******************************/

template <typename T>
void Heap<T>::insert(T value) {
   values.push_back(value); // Add the new value at the end of the vector
    // Heapify the vector to maintain the heap property
    int index = values.size() - 1;
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (values[index] < values[parentIndex]) { // Adjust this condition for max heap
            std::swap(values[index], values[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

/*******************************/
/* delete values from the heap */
/*******************************/

template <typename T>
void Heap<T>::remove(T value) {
    auto it = std::find(values.begin(), values.end(), value); // Find the index of the value to be removed

    if (it == values.end()) { // If the value is not found, exit the function
        return;
    }

    int index = it - values.begin(); // Get the index of the value

    std::swap(values[index], values[values.size() - 1]); // Swap the value with the last element
    values.pop_back(); // Remove the last element from the heap

    // Check if the swapped value violates the heap property
    if (index < values.size()) {
        if (index == 0 || values[index] > values[(index - 1) / 2]) { // If the value is larger than its parent
            // Perform a downward heapify operation
            heapify(index);
        } else {
            // If the value is smaller than its parent, perform an upward heapify operation
            while (index > 0 && values[index] < values[(index - 1) / 2]) {
                std::swap(values[index], values[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
        }
    }
}


/*******************************/
// find the smallest value in the heap
/*******************************/

template <typename T>
T Heap<T>::getMin() {
      if (values.empty()) {
        throw std::out_of_range("Heap is empty");
    }
    return values[0]; // Return the value at the root (smallest value in a min heap)
}

/*******************************/
// private function to heapify a given 'node'
/*******************************/

template <typename T>
void Heap<T>::heapify(int parent_index) {
  // if we're outside the index range, return
  if (parent_index < 0 || parent_index >= values.size()) return;

  // find children indexes
  int left_child_index = parent_index * 2 + 1;
  int right_child_index = parent_index * 2 + 2;

  // if parent is larger than child, swap with smallest child
  int index_of_smallest = parent_index;

  // check if left child exists and if exists, is smallest value there
  if (left_child_index < values.size() &&
      values.at(left_child_index) < values.at(index_of_smallest)) {
    // make this index the current smallest
    index_of_smallest = left_child_index;
  }

  // check if left child exists and if exists, is smallest value there
  if (right_child_index < values.size() &&
      values.at(right_child_index) < values.at(index_of_smallest)) {
    // make this index the current smallest
    index_of_smallest = right_child_index;
  }

  // if parent is not smallest, swap with smallest child
  if (index_of_smallest != parent_index) {
    T temp = values.at(parent_index);
    values.at(parent_index) = values.at(index_of_smallest);
    values.at(index_of_smallest) = temp;

    // heapify the swapped index - it may need to move
    // further down the 'tree'
    heapify(index_of_smallest);
  }
}

#endif