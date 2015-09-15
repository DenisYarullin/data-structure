#ifndef DEQUE_H_
#define DEQUE_H_

#include "doubly_linked_list.h"

template <typename T>
class Deque
{
private:
	DoublyLinkedList *list;
public:
	Deque() : list(new DoublyLinkedList) {};
	~Deque() { delete list; };
	void EnqueueFirst(T value);
	void EnqueueLast(T value);
	T DequeueFirst();
	T DequeueLast();
	T PeekFirst();
	T PeekLast();
	int Count() { return list->Count(); }
};

template <typename T>
void Deque<T>::EnqueueFirst(T value)
{
	list->AddFirst(value);
}

template <typename T>
void Deque<T>::EnqueueLast(T value)
{
	list->AddLast(value);
}

template <typename T>
T Deque<T>::DequeueFirst()
{
	if (list->Count() == 0)
	{
		throw exception("DequeueFirst called when deque is empty");
	}
	T temp = list->GetHeadValue();
	list->RemoveFirst();
	return temp;
}

template <typename T>
T Deque<T>::DequeueLast()
{
	if (list->Count() == 0)
	{
		throw exception("DequeueLast called when deque is empty");
	}
	T temp = list->GetTailValue();
	list->RemoveLast();
	return temp;
}

template <typename T>
T Deque<T>::PeekFirst()
{
	if (list->Count() == 0)
	{
		throw exception("DequeueFirst called when deque is empty");
	}
	return 	list->GetHeadValue();;
}

template <typename T>
T Deque<T>::PeekLast()
{
	if (list->Count() == 0)
	{
		throw exception("DequeueLast called when deque is empty");
	}
	return list->GetTailValue();;
}

#endif // DEQUE_H_