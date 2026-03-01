#include "List.hpp"

template <typename T>
List<T>::List() : head(nullptr), length(0) {}

template <typename T>
List<T>::~List()
{
  clear();
}

template <typename T>
List<T>::List(const List<T>& x) : head(nullptr), length(0) {
  Node<T>* src = x.head;
  for (std::size_t i = 0; i < x.length; i++) {
    insert(i, src -> getItem());
    src = src -> getNext();
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x) {
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) {
  std::swap(head, x.head);
  std::swap(length, x.length);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return length == 0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  return length;
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item) {
  if (position > length)
    throw std::out_of_range("insert: position out of range");

  if (position == 0) {
    head = new Node<T>(item, head);
  } 
  else {
    Node<T>* prev = head;
    for (std::size_t i = 0; i < position - 1; i++)
      prev = prev->getNext();
    prev -> setNext(new Node<T>(item, prev -> getNext()));
  }
  length++;
}

template <typename T>
void List<T>::remove(std::size_t position) {
  if (position >= length)
    throw std::out_of_range("remove: position out of range");

  Node<T>* toDelete;
  if (position == 0) {
    toDelete = head;
    head = head -> getNext();
  } else {
    Node<T>* prev = head;
    for (std::size_t i = 0; i < position - 1; i++)
      prev = prev -> getNext();
    toDelete = prev -> getNext();
    prev -> setNext(toDelete -> getNext());
  }
  delete toDelete;
  length--;
}

template <typename T>
void List<T>::clear() {
  while (head != nullptr) {
    Node<T>* toDelete = head;
    head = head->getNext();
    delete toDelete;
  }
  length = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const {
  if (position >= length)
    throw std::out_of_range("getEntry: position out of range");

  Node<T>* cur = head;
  for (std::size_t i = 0; i < position; i++)
    cur = cur -> getNext();
  return cur -> getItem();
}


template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue) {
  if (position >= length)
    throw std::out_of_range("setEntry: position out of range");

  Node<T>* cur = head;
  for (std::size_t i = 0; i < position; i++)
    cur = cur -> getNext();
  cur -> setItem(newValue);
}

template <typename T>
void List<T>::moveEntry(std::size_t from, std::size_t to) {
  if (from >= length || to >= length)
    throw std::out_of_range("moveEntry: position out of range");

  if (from == to) 
    return;
    
  T item = getEntry(from);
  remove(from);
  insert(to, item);
}
