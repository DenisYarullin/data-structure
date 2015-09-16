#ifndef STACK_BASED_STACK_H_
#define STACK_BASED_STACK_H_

#include "deque.h"

template <typename T>
class Stack
{
private:
	Deque *deque;
public:
	Stack() : deque(new Deque) {}
	~Stack() { delete deque; }
	void Push(T value);
	T Pop();
	T Peek();
	int Count() { deque->Count(); };
};

template <typename T>
void Stack<T>::Push(T value)
{
	deque->EnqueueFirst();
}

template <typename T>
T Stack<T>::Pop()
{
	deque->DequeueFirst();
}

template <typename T>
T Stack<T>::Peek()
{
	deque->PeekFirst();
}

#endif // STACK_BASED_STACK_H_