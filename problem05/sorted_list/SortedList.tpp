#include "SortedList.hpp"
#include <stdexcept>
#include <cstdlib>

template <typename T>
SortedList<T>::SortedList()
{
  // base constructor gets called automatically
}

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list) 
{
  for (std::size_t i = 0; i < unsorted_list.getLength(); i++){
    insert(unsorted_list.getEntry(i));
  }
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> & x):
  List<T>(x)
{
}

template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
}

template <typename T>
SortedList<T>::~SortedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
}

template <typename T>
std::size_t SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
}

template <typename T>
void SortedList<T>::insert(const T& item)
{
  std::size_t pos = 0;
  std::size_t len = List<T>::getLength();
  while (pos < len && !(item < List<T>::getEntry(pos))){
    pos++;
  }

  List<T>::insert(pos, item);

}

template <typename T>
void SortedList<T>::remove(const T& item)
{  
  std::size_t pos = getPosition(item);
  List<T>::remove(pos);
}

template <typename T>
void SortedList<T>::removeAt(std::size_t position)
{  
  List<T>::remove(position);
}

template <typename T>
void SortedList<T>::clear()
{
  List<T>::clear();
}

template <typename T>
T SortedList<T>::getEntry(std::size_t position) const
{
  return List<T>::getEntry(position);
}

template <typename T>
std::size_t SortedList<T>::getPosition(const T& item)
{
  std::size_t len = List<T>::getLength();
  for (std::size_t i = 0; i < len; i++){
    if (!(List<T>::getEntry(i) < item) && !(item < List<T>::getEntry(i))){
      return i;
    }
  }
  throw std::invalid_argument("getPosition item not found");
}
