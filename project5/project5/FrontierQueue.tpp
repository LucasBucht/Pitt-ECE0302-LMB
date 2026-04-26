#include "FrontierQueue.hpp"

template <typename T>
State<T> FrontierQueue<T>::pop() {
  // Swap root with last, remove last, shift down
  State<T> top = queue[0];
  queue[0] = queue.back();
  queue.pop_back();

  std::size_t i = 0;
  std::size_t n = queue.size();

  while (true) {
    std::size_t left = 2 * i + 1;
    std::size_t right = 2 * i + 2;
    std::size_t smallest = 1;

    if (left < n && queue[left].getFCost() < queue[smallest].getFCost()) {
      smallest = left;
    }
    if (right < n && queue[right].getFCost() < queue[smallest].getFCost()) {
      smallest = right;
    }

    if (smallest != 1) {
      std::swap(queue[i], queue[smallest]);
      i = smallest;
    } else {
      break;
    }
  }

  return top;
}

template <typename T>
void FrontierQueue<T>::push(const T &p, std::size_t cost, std::size_t heur) {
  // Add to end, bubble up
  queue.push_back(State<T>(p, cost, heur));

  std::size_t i = queue.size() - 1;
  while (i > 0) {
    std::size_t parent = (i - 1) / 2;
    if (queue[parent].getFCost() > queue[i].getFCost()) {
      std::swap(queue[parent], queue[i]);
      i = parent;
    } else {
      break; 
    }
  }
}

template <typename T>
bool FrontierQueue<T>::empty() const {
  return queue.empty();
}

template <typename T> 
bool FrontierQueue<T>::contains(const T &p) const {
  for (const auto &s : queue) {
    if (s.getValue() == p) {
      return true;
    }
  }
  return false;
}

template <typename T>
void FrontierQueue<T>::replaceif(const T &p, std::size_t cost) {

  //TODO

}


