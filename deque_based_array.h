#ifndef DEQUE_BASED_ARRAY_H_
#define DEQUE_BASED_ARRAY_H_

template <typename T>
class Deque
{
private:
	int size;
	int length;
	int head;
	int tail;
	T *items;
public:
	Deque() : size(0), length(0), head(0), tail(-1), items(nullptr) {}
	~Deque() { delete[] items; }
	void EnqueueFirst(T item);
	void EnqueueLast(T item);
	T DequeueFirst();
	T DequeueLast();
	T PeekFirst();
	T PeekLast();
	int Count() { return size; }
private:
	void allocateNewArray(int startingIndex);

};

// �������� startingIndex ������������, ����� ��������, ������� ����� � ������ ���������� �������� �������
// (� ������ ���������� � ������).
template <typename T>
void Deque<T>::allocateNewArray(int startingIndex)
{
	int newLength = (length == 0) ? 4 : length << 1;
	T *newArray = new T[newLength];

	if (size > 0)
	{
		int targetIndex = startingIndex;
		// �������� ����������
		// ���� ������ �� �����������, ������ �������� ��������.
		// � ��������� ������, �������� �� head �� �����, � � ����� �� ������ �� tail

		// ���� tail ������, ��� head, ��������� � ������
		if (tail < head)
		{
			// �������� items[head] ... items[end] � newArray[0] ... newArray[N]
			for (int index = head; index < size; index++)
			{
				newArray[targetIndex] = items[index];
				targetIndex++;
			}

			// �������� items[0] ... items[tail] � newArray[N+1] ...
			for (int index = 0; index <= tail; index++)
			{
				newArray[targetIndex] = items[index];
				targetIndex++;
			}

		}
		else
		{
			// �������� items[head] ... items[tail] � newArray[0] ... newArray[N]
			for (int index = head; index <= tail; index++)
			{
				newArray[targetIndex] = items[index];
				targetIndex++;
			}
		}
		head = startingIndex;
		tail = targetIndex - 1;
	}
	else
	{
		// ������ ����
		head = 0;
		tail = -1;
	}

	delete[] items;
	length = newLength;
	items = newArray;
}

template <typename T>
void Deque<T>::EnqueueFirst(T item)
{
	// ��������, ���������� �� ���������� �������
	if (length == size)
	{
		allocateNewArray(1);
	}

	// ��� ��� ������ �� �������� � head ������ 0,
	// �� ������, ��� ���� ����� � ������ �������.
	if (head > 0)
	{
		head--;
	}
	else
	{
		head = length - 1;
	}

	items[head] = item;
	size++;
}

template <typename T>
void Deque<T>::EnqueueLast(T item)
{
	// ��������, ���������� �� ���������� �������:
	if (length == size)
	{
		allocateNewArray(0);
	}

	// ������, ����� � ��� ���� ���������� ������, 
	// ���� tail � ����� �������, ��� ���� ������� � ������.
	if (tail == length - 1)
	{
		tail = 0;
	}
	else
	{
		tail++;
	}

	items[tail] = item;
	size++;
}

template <typename T>
T Deque<T>::DequeueFirst()
{
	if (size == 0)
	{
		throw exception("The deque is empty");
	}

	T value = items[head];

	if (head == length - 1)
	{
		// ���� head ���������� �� ��������� �������, ��������� � ������ �������
		head = 0;
	}
	else
	{
		// ��������� � ���������� ��������.
		head++;
	}

	size--;
	return value;
}

template <typename T>
T Deque<T>::DequeueLast()
{
	if (size == 0)
	{
		throw exception("The deque is empty");
	}

	T value = items[tail];

	if (tail == 0)
	{
		// ���� tail ���������� �� ������ �������, ��������� � �����
		tail = length - 1;
	}
	else
	{
		// ��������� � ����������� ��������
		tail--;
	}

	size--;
	return value;
}

template <typename T>
T Deque<T>::PeekFirst()
{
	if (size == 0)
	{
		throw exception("The deque is empty");
	}

	return items[head];
}

template <typename T>
T Deque<T>::PeekLast()
{
	if (size == 0)
	{
		throw exception("The deque is empty");
	}

	return items[tail];
}

#endif // DEQUE_BASED_ARRAY_H_

