#include "ArrayList.hpp"

template <typename T>
ArrayList<T>::ArrayList()
  : items(nullptr), length(0)
{
}

template <typename T>
ArrayList<T>::~ArrayList()
{
  delete[] items;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& x)
  : items(nullptr), length(x.length)
{
  if (length > 0)
  {
    items = new T[length];
    for (std::size_t i = 0; i < length; i++)
      items[i] = x.items[i];
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList x)
{
  swap(x);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &x)
{
  std::swap(items, x.items);
  std::swap(length, x.length);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  return length == 0;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept
{
  return length;
}

template <typename T>
void ArrayList<T>::insert(std::size_t position, const T& item)
{
  if (position > length)
    throw std::out_of_range("insert position invalid");

  T* newItems = new T[length + 1];

  for (std::size_t i = 0; i < position; i++)
    newItems[i] = items[i];

  newItems[position] = item;

  for (std::size_t i = position; i < length; i++)
    newItems[i + 1] = items[i];

  delete[] items;
  items = newItems;
  length++;
}


template <typename T>
void ArrayList<T>::remove(std::size_t position)
{
  if (position >= length)
    throw std::out_of_range("remove position invalid");

  if (length == 1)
  {
    delete[] items;
    items = nullptr;
    length = 0;
    return;
  }

  T* newItems = new T[length - 1];

  for (std::size_t i = 0; i < position; i++)
    newItems[i] = items[i];

  for (std::size_t i = position + 1; i < length; i++)
    newItems[i - 1] = items[i];

  delete[] items;
  items = newItems;
  length--;
}

template <typename T>
void ArrayList<T>::clear()
{
  delete[] items;
  items = nullptr;
  length = 0;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  if (position >= length)
    throw std::out_of_range("getEntry position invalid");

  return items[position];
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position >= length)
    throw std::out_of_range("setEntry position invalid");

  items[position] = newValue;
}
