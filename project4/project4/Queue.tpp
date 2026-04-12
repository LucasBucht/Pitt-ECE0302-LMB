#include "Queue.hpp"

template <typename T, typename L>
void Queue<T,L>::enqueue(const T& item)
{
  internal_list.insert(internal_list.getLength(), item);
}

template <typename T, typename L>
void Queue<T,L>::dequeue()
{
  if (internal_list.isEmpty()){
    throw std::out_of_range("Queue::dequeue: queue is empty");
  }
  internal_list.remove(0);
}

template <typename T, typename L>
T Queue<T,L>::peekFront() const
{
  if (internal_list.isEmpty()){
    throw std::out_of_range("Queue::peekFront: queue is empty");
  }
  return internal_list.getEntry(0);
}

template <typename T, typename L>
bool Queue<T,L>::isEmpty() const
{
  return internal_list.isEmpty();
}

