#include "List.hpp"
#include <stdexcept>

template <typename T>
List<T>::List() : head(nullptr), length(0)
{
}

template <typename T>
List<T>::~List()
{
  clear();
}

template <typename T>
List<T>::List(const List<T>& x)
{
  //TODO
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
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
void List<T>::insert(std::size_t position, const T& item)
{
  if (position > length){
    throw std::out_of_range("List::insert: position out of range");
  }
  if (position == 0){
    head = new Node(item, head);
  } else {
    Node* cur = head;
    for (std::size_t i = 0; i < position - 1; i++){
      cur = cur -> next;
    }
    cur -> next = new Node(item, cur -> next);
  }
  length++;
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  if (position >= length){
    throw std::out_of_range("List::remove: position out of range");
  }
  if (position == 0){
    Node* temp = head;
    head = head -> next;
    delete temp;
  } else {
    Node* cur = head;
    for (std::size_t i = 0; i < position - 1; i++){
      cur = cur -> next;
    }
    Node* temp = cur -> next;
    cur -> next = temp -> next;
    delete temp;
  }
  length--;
}

template <typename T>
void List<T>::clear()
{
  while (head != nullptr){
    Node* temp = head;
    head = head -> next;
    delete temp;
  }
  length = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  if (position >= length){
    throw std::out_of_range("List::getEntry: position out of range");
  }
  Node* cur = head;
  for (std::size_t i = 0; i < position; i++){
    cur = cur -> next;
  }
  return cur -> data;
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
}
