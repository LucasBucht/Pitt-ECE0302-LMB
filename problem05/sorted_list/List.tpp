#include "List.hpp"

template <typename T>
List<T>::List() : head(nullptr), size(0)
{
}

template <typename T>
List<T>::~List()
{
  clear();
}

template <typename T>
List<T>::List(const List<T>& x) : head(nullptr), size(0)
{
  Node<T>* cur = x.head;
  while (cur){
    instert(size, cur -> getItem());
    cur = cur -> getNext();
  }
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List& x) 
{
  std::swap(head, x.head);
  std::swap(size, x.size);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return size == 0;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
  if (position > size){
    throw std::out_of_range("insert position out of range")
  }

  Node<T>* node = new Node<T>(item);
  if (position == 0){
    node -> setNext(head);
    head = node;
  } else {
    Node<T>* prev = head;
    for (std::size_t i = 0; i < position; i++){
      prev = prev -> getNext();
    }
    node -> setNext(prev -> getNext());
    prev -> setnext(node);
  }

  size++;

}

template <typename T>
void List<T>::remove(std::size_t position)
{
  if (position >= size){
    throw std::out_of_range("remove position out of range");
  }

  Node<T>* del;
  if (position == 0){
    del = head;
    head = head -> getNext();
  } else {
    Node<T>* prev = head;
    for (std::size_t i = 0; i < position - 1; i++){
      prev = prev -> getNext();
    }
    del = prev -> getNext();
    prev -> setNext(del -> getNext());
  }

  delete del;
  size--;

}

template <typename T>
void List<T>::clear()
{
  while (head){
    Node<T>* del = head;
    head = head -> getNext();
    delete del;
  }

  size = 0;

}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  If (position >= size){
    throw std::out_of_range("getEntry position out of range");
  }

  Node<T>* cur = head;
  for (std::size_t i = 0; i < position; i++){
    cur = cur -> getNext();
  }

  return cur -> getItem();

}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position >= size){
    throw std::out_of_range("setEntry position out of range");
  }

  Node<T>* cur = head;
  for (std::size_t i = 0; i < position; i++){
    cur = cur -> getNext();
  }

  cur -> setItem(newValue);

}
