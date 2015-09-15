#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

template <typename T>
struct Node
{
	Node(T value_) : value(value_),  previous(nullptr), next(nullptr) {}
	T value;
	Node *previous;
	Node *next;
};

template <typename T>
class DoublyLinkedList
{
public:
	DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
	void AddFirst(T value);
	void AddLast(T value);
	void Add(T value);
	void RemoveFirst();
	void RemoveLast();
	bool Remove(T item);
	int Count() { return count;  }
	T GetTailValue() { return tail->value; }
	T GetHeadValue() { return head->value; }
private:
	Node<T> *head;
	Node<T> *tail;
	int count;

};

template <typename T>
void DoublyLinkedList<T>::AddFirst(T value)
{
	Node<T> *node = new Node<T>(value);
	//��������� ������ �� ������ �������
	Node<T> *temp = head;
	//head ��������� �� ����� ����
	head = node;
	//��������� ������ ������ ������� ��������
	head->next = temp;
	if (count == 0)
	{
		// ���� ������ ��� ����, �� head � tail ������ ��������� �� ����� ����
		tail = head;
	}
	else
	{
		temp->previous = head;
	}
	count++;
}


template <typename T>
void DoublyLinkedList<T>::AddLast(T value)
{
	Node<T> *node = new Node<T>(value);
	if (count == 0)
	{
		head = node;
	}
	else
	{
		tail->next = node;
		node->previous = tail;
	}
	tail = node;
	count++;
}

template <typename T>
void DoublyLinkedList<T>::Add(T value)
{
	AddLast(value);
}

template <typename T>
void DoublyLinkedList<T>::RemoveFirst()
{
	if (count != 0)
	{
		Node<T> *oldHead = head;
		head = head->next;
		delete oldHead;
		count--;
		if (count == 0)
		{
			tail = nullptr;
		}
		else
		{
			head->previous = nullptr;
		}
	}
}

template <typename T>
void DoublyLinkedList<T>::RemoveLast()
{
	if (count != 0)
	{
		if (count == 1)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			Node<T> *oldTail = tail;
			tail = tail->previous;
			tail->next = nullptr;
			delete oldTail;
		}
		count--;
	}
}

template <typename T>
bool DoublyLinkedList<T>::Remove(T item)
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
			// ���� � �������� ��� � �����
			if (previous != nullptr)
			{
				// ������ 3b
				previous->next = current->next;
				// ���� � �����, �� ������ tail
				if (current->next == nullptr)
				{
					tail = previous;
				}
				else
				{
					current->next->previous = previous;
				}
				count--;
				delete current;
			}
			else
			{
				RemoveFirst();
			}
			return true;
		}
		previous = current;
		current = current->next;
	}
	return false;
}
#endif // DOUBLY_LINKED_LIST_H_