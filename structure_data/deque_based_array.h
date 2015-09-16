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

// Параметр startingIndex используется, чтобы показать, сколько полей в начале необходимо оставить пустыми
// (в случае добавления в начало).
template <typename T>
void Deque<T>::allocateNewArray(int startingIndex)
{
	int newLength = (length == 0) ? 4 : length << 1;
	T *newArray = new T[newLength];

	if (size > 0)
	{
		int targetIndex = startingIndex;
		// Копируем содержимое
		// Если массив не закольцован, просто копируем элементы.
		// В противном случае, копирует от head до конца, а а затем от начала до tail

		// Если tail меньше, чем head, переходим в начало
		if (tail < head)
		{
			// Копируем items[head] ... items[end] в newArray[0] ... newArray[N]
			for (int index = head; index < size; index++)
			{
				newArray[targetIndex] = items[index];
				targetIndex++;
			}

			// Копируем items[0] ... items[tail] в newArray[N+1] ...
			for (int index = 0; index <= tail; index++)
			{
				newArray[targetIndex] = items[index];
				targetIndex++;
			}

		}
		else
		{
			// Копируем items[head] ... items[tail] в newArray[0] ... newArray[N]
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
		// массив пуст
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
	// Проверим, необходимо ли увеличение массива
	if (length == size)
	{
		allocateNewArray(1);
	}

	// Так как массив не заполнен и head больше 0,
	// Мы знаемм, что есть место в начале массива.
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
	// Проверим, необходимо ли увеличение массива:
	if (length == size)
	{
		allocateNewArray(0);
	}

	// Теперь, когда у нас есть подходящий массив, 
	// если tail в конце массива, нам надо перейте в начало.
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
		// Если head установлен на последнем индексе, переходим в начало массива
		head = 0;
	}
	else
	{
		// Переходим к следующему элементу.
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
		// Если tail установлен на начало массива, переходим к концу
		tail = length - 1;
	}
	else
	{
		// Переходим к предыдущему элементу
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

