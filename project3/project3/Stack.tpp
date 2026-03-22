#include <stdexcept>

#include "Stack.hpp"

template<class ItemType>
Stack<ItemType>::Stack() : headPtr(nullptr), currentSize(0) 
{
} 

template<class ItemType>
Stack<ItemType>::~Stack()
{
	clear();
}

template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return currentSize == 0;
}

template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}

template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNode = new Node<ItemType>(newItem, headPtr);
	headPtr = newNode;
	currentSize++;
	return true;
}

template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	if (isEmpty()) {
		throw std::logic_error("peek() cannot be called on an empty stack");
	}
	return headPtr -> getItem();
}

template<class ItemType>
bool Stack<ItemType>::pop() 
{
	if (isEmpty()){
		return false;
	}
	Node<ItemType>* toDelete = headPtr;
	headPtr = headPtr -> getNext();
	delete toDelete;
	currentSize--;
	return true;
}

template<class ItemType>
void Stack<ItemType>::clear()
{
	while (!isEmpty()){
		pop();
	}
}

