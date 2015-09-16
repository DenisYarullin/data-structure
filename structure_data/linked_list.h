#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

template <typename T>
struct Node
{
	Node(T value_) : value(value_), next(nullptr) {}
	T value;
	Node * next;
};

template <typename T>
class LinkedList
{
public:
	LinkedList() : count(0), head(nullptr), tail(nullptr) {}
	void Add(T item);
	void Clear();
	bool Contains(T item);
	int Count();
	bool Remove(T item);
private:
	Node<T> *head;
	Node<T> *tail;
	int count;
};

template <typename T>
void LinkedList<T>::Add(T item)
{
	Node<T> *node = new Node<T>(item);
	if (head == nullptr)
	{
		head = tail = node;
	}
	else
	{
		tail->next = node;
		tail = node;
		node->next = nullptr;
	}
	count++;
}

template <typename T>
bool LinkedList<T>::Remove(T item)
{
	Node<T> *previous = nullptr;
	Node<T> *current = head;
	// 1: ������ ������: ������ �� ������.
	// 2: ���� �������: ���������� Previous = null.
	// 3: ��������� ���������:
	//    a: ��������� ������� ������.
	//    b: ��������� ������� � �������� ��� �����.
	while (current != nullptr)
	{
		if (current->value == item)
		{
			// ���� � �������� ��� � �����.
			if (previous != nullptr)
			{
				// ������ 3b.
				previous->next = current->next;
				// ���� � �����, �� ������ _tail.
				if (current->next == nullptr)
				{
					tail = previous;
				}
			}
			else
			{
				// ������ 2 ��� 3a.
				head = head->next;
				// ������ ������ ������?
				if (head == nullptr)
				{
					tail = nullptr;
				}
			}
			count--;
			delete current;
			return true;
		}
		previous = current;
		current = current->next;
	}
}


template <typename T>
bool LinkedList<T>::Contains(T item)
{
	Node<T> *current = head;
	while (current != nullptr)
	{
		if (current->value == item)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}


template <typename T>
void LinkedList<T>::Clear()
{
	Node<T> *previous = nullptr;
	Node<T> *current = head;

	while (current != nullptr)
	{
		previous = current;
		current = current->next;
		count--;
		delete previous;
	}
}

template <typename T>
int LinkedList<T>::Count()
{
	return count;
}

#endif // LINKED_LIST_H_

