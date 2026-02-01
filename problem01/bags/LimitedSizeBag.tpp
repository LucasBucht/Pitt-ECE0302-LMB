#include "LimitedSizeBag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() : itemCount(0) {}
  
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  if (itemCount >= maxsize)
    return false;

  items[itemCount] = item;
  itemCount++;
  return true;
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  for (std::size_t i = 0; i < itemCount; i++){
    if (items[i] == item){
      items[i] = items[itemCount - 1];
      itemCount--;
      return true;
    }
  }
  return false;
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  return itemCount == 0;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return itemCount;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  for (std::size_t i = 0; i < itemCount; i++){
    if (items[i] == item)
      return true;
  }
  return false;
}

template<typename T>
void LimitedSizeBag<T>::clear(){
  itemCount = 0;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t count = 0;
  for (std::size_t i = 0; i < itemCount; i++){
    if (items[i] == item)
      count++;
  }
  return count;
};
