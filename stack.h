#ifndef STACK_H_
#define STACK_H_

#include "doubly_linked_list.h"

template <typename T>
class Stack
{
private:
	DoublyLinkedList *list;
public:
	Stack() : list(new DoublyLinkedList) {}
	~Stack() { delete list; }
	void Push(T value);
	T Pop();
	T Peek();
	int Count() { return list->Count();  }
};

template <typename T>
void Stack<T>::Push(T value)
{
	list->AddLast(value);
}

template <typename T>
T Stack<T>::Pop()
{
	if (list->Count() == 0)
	{
		throw exception("The stack is empty");
	}

	T result = list->GetTailValue();
	list->RemoveLast();
	return result;
}

template <typename T>
T Stack<T>::Peek()
{
	if (list->Count() == 0)
		throw exception("The stack is empty");
	return list->GetTailValue();
}




#endif // STACK_H_