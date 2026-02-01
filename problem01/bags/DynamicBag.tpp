#include "DynamicBag.hpp"
#include <utility>

template<typename T>
DynamicBag<T>::DynamicBag() : items(nullptr), itemCount(0) {}
  

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x) : items(nullptr), itemCount(x.itemCount) {
  if (itemCount > 0){
    items = new T[itemCount];
    for (std::size_t i = 0; i < itemCount; i++;){
      items[i] = x.items[i];
    }
  }
}
    
template<typename T>
DynamicBag<T>::~DynamicBag() {
  delete[] items;
}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{  
  swap(x);
  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){
  std::swap(items, x.items);
  std::swap(itemCount, x.itemCount);
}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  T* newItems = new T[itemCount + 1];
  for (std::size_t i = 0; i < itemCount; i++){
    newItems[i] = items[i];
  }

  newItems[itemCount] = item;

  delete[] items;
  items = newItems;
  itemCount++;
  
  return true;
}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  std::size_t index = itemCount;
  for (std::size_t i = 0; i < itemCount; i++){
    if (items[i] == item){
      index = i;
      break;
    }
  }

  if (index == itemCount)
    return false;

  if (itemCount == 1){
    delete[] items;
    items = nullptr;
    itemCount = 0;
    return true;
  }

  T* newItems = new T[itemCount - 1];
  for (std::size_t i = 0, j = 0; i < itemCount; i++){
    if (i != index)
      newItems[j++] = items[i];
  }

  delete[] items;
  items = newItems;
  itemCount--;

  return true;
}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  return itemCount == 0;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return itemCount;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  for (std::size_t i = 0; i < itemCount; i++){
    if (items[i] == item)
      return true;
  }
  return false;
}

template<typename T>
void DynamicBag<T>::clear()
{
  delete[] items;
  items = nullptr;
  itemCount = 0;
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t count = 0;
  for (std::size_t i = 0; i < itemCount; i++){
    if (items[i] == item)
      count++
  }
  return count;
};
