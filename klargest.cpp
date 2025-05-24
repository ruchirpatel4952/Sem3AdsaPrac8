#include <vector>
#include <queue>
#include <functional>  // for greater

int kth_largest(std::vector<int> values, int k) {
  // use a min-heap to keep track of the k largest elements
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

  for (int value : values) {
    min_heap.push(value);
    if (min_heap.size() > static_cast<std::vector<int>::size_type>(k)) {
      min_heap.pop();
    }
  }

  return min_heap.top();  // the kth largest element
}
