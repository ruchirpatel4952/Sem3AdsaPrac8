#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <cmath>  // for floor

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
  for (typename std::vector<T>::size_type i = 0; i < start_values.size(); i++) {
    values.push_back(start_values.at(i));
  }

  // starting from last non-leaf node (last parent), heapify each
  // of the parents
  int initial_parent_index = floor(values.size() / 2) - 1;
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
  // add the new value to the end of the vector
  values.push_back(value);

  // bubble up the new value to maintain the heap property
  int index = values.size() - 1;
  int parent_index = (index - 1) / 2;

  while (index > 0 && values[index] < values[parent_index]) {
    std::swap(values[index], values[parent_index]);
    index = parent_index;
    parent_index = (index - 1) / 2;
  }
}

/*******************************/
/* delete values from the heap */
/*******************************/

template <typename T>
void Heap<T>::remove(T value) {
  // find the index of the value to remove
  typename std::vector<T>::size_type index = -1;
  for (typename std::vector<T>::size_type i = 0; i < values.size(); i++) {
    if (values[i] == value) {
      index = i;
      break;
    }
  }
  if (index == static_cast<typename std::vector<T>::size_type>(-1)) return;  // value not found

  // replace the value to remove with the last value in the vector
  values[index] = values.back();
  values.pop_back();

  // bubble down to maintain the heap property
  heapify(index);
}

/*******************************/
// find the smallest value in the heap
/*******************************/

template <typename T>
T Heap<T>::getMin() {
  // return the root value, which is the smallest in a min-heap
  if (!values.empty()) {
    return values[0];
  }
  throw std::out_of_range("Heap is empty");
}

/*******************************/
// private function to heapify a given 'node'
/*******************************/

template <typename T>
void Heap<T>::heapify(int parent_index) {
  // if we're outside the index range, return
  if (parent_index < 0 || parent_index >= static_cast<int>(values.size())) return;

  // find children indexes
  int left_child_index = parent_index * 2 + 1;
  int right_child_index = parent_index * 2 + 2;

  // if parent is larger than child, swap with smallest child
  int index_of_smallest = parent_index;

  // check if left child exists and if exists, is smallest value there
  if (left_child_index < static_cast<int>(values.size()) &&
      values.at(left_child_index) < values.at(index_of_smallest)) {
    // make this index the current smallest
    index_of_smallest = left_child_index;
  }

  // check if left child exists and if exists, is smallest value there
  if (right_child_index < static_cast<int>(values.size()) &&
      values.at(right_child_index) < values.at(index_of_smallest)) {
    // make this index the current smallest
    index_of_smallest = right_child_index;
  }

  // if parent is not smallest, swap with smallest child
  if (index_of_smallest != parent_index) {
    std::swap(values[parent_index], values[index_of_smallest]);
    heapify(index_of_smallest);  // recursively heapify the affected subtree
  }
}

#endif
