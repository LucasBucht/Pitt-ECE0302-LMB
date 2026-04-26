#include "FrontierQueue.hpp"

template <typename T>
State<T> FrontierQueue<T>::pop() {

  //TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.

  return State<T>(T(),0,0);
}

template <typename T>
void FrontierQueue<T>::push(const T &p, std::size_t cost, std::size_t heur) {
  // Add to end, bubble up
  queue.push_back(State<T>(p. cost, heur));

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


