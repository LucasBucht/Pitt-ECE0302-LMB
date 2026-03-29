#include "ListIterator.hpp"

/* Change the second constructor argument to Node<T>* if using a linked implementation */
template <typename T>
inline ListIterator<T>::ListIterator(List<T> *listPtr, T *itemPtr) 
    : listPtr(listPtr), nodePtr(nodePtr)
{
}

template <typename T>
inline T ListIterator<T>::operator*() const
{
    return nodePtr -> getItem();
}

template <typename T>
inline ListIterator<T> ListIterator<T>::operator++()
{
    nodePtr = nodePtr -> getNext();
    return *this;
}

template <typename T>
inline bool ListIterator<T>::operator==(const ListIterator<T> &rhs) const
{
    return nodePtr == rhs.nodePtr;
}

template <typename T>
inline bool ListIterator<T>::operator!=(const ListIterator<T> &rhs) const
{
    return nodePtr != rhs.nodePtr;
}