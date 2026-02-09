#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList()
  : head(nullptr), length(0)
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
  : head(nullptr), length(0)
{
  Node<T>* curr = x.head;
  while (curr)
  {
    insert(length, curr->getItem());
    curr = curr->getNext();
  }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x)
{
  std::swap(head, x.head);
  std::swap(length, x.length);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return length == 0;
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return length;
}

template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
  if (position > length)
    throw std::out_of_range("insert position invalid");

  if (position == 0)
  {
    head = new Node<T>(item, head);
  }
  else
  {
    Node<T>* prev = getNode(position - 1);
    prev->setNext(new Node<T>(item, prev->getNext()));
  }

  length++;
}

template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
  if (position >= length)
    throw std::out_of_range("remove position invalid");

  Node<T>* toDelete;

  if (position == 0)
  {
    toDelete = head;
    head = head->getNext();
  }
  else
  {
    Node<T>* prev = getNode(position - 1);
    toDelete = prev->getNext();
    prev->setNext(toDelete->getNext());
  }

  delete toDelete;
  length--;
}

template <typename T>
void LinkedList<T>::clear()
{
  while (head)
  {
    Node<T>* temp = head;
    head = head->getNext();
    delete temp;
  }
  length = 0;
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if (position >= length)
    throw std::out_of_range("getEntry position invalid");

  return getNode(position)->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position >= length)
    throw std::out_of_range("setEntry position invalid");

  getNode(position)->setItem(newValue);
}
