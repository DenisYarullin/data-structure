#ifndef QUEUE_H_
#define QUEUE_H_

#include "doubly_linked_list.h"

template <typename T>
class Queue
{
private:
	DoublyLinkedList *list;
public:
	Queue() : list(new DoublyLinkedList) {}
	~Queue() { delete list; }
	void Enqueue(T value);
	T Dequeue();
	T Peek();
	int Count() { return list->Count(); }
};

template <typename T>
void Queue<T>::Enqueue(T value)
{
	list->AddFirst(value);
}

template <typename T>
T Queue<T>::Dequeue()
{
	if (list->Count() == 0)
		throw exception("The queue is empty");
	T last = list->GetTailValue();
	list->RemoveLast();
	return last;
}

template <typename T>
T Queue<T>::Peek()
{
	if (list->Count() == 0)
		throw exception("The queue is empty");
	return list->GetTailValue();
}

#endif // QUEUE_H_