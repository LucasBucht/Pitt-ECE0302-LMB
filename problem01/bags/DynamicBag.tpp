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
DynamicBag<T>::~DynamicBag(){}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{  
  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  return false;
}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  return false;
}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  return false;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return 0;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  return false;
}

template<typename T>
void DynamicBag<T>::clear(){}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  return 0;
};
