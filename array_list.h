#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

template <typename T>
class ArrayList
{
private:
	int length;
	int count;
	T *items;
public:
	ArrayList() : length(0), count(0), items(nullptr) {}
	ArrayList(int length_) : length(length_), count(0)
	{
		if (length < 0)
		{
			throw length_error("length");
		}
		items = new T[length];
	}
	ArrayList(const ArrayList &other);
	ArrayList &operator=(const ArrayList &other);
	T &operator[](int index) { return items[index]; }
	~ArrayList() { delete[] items; }
	void swap(ArrayList &other);
	int IndexOf(T item);
	void Insert(int index, T item);
	void RemoveAt(int index);
	void Add(T item);
	void Clear() { count = 0; lenght = 0; delete [] items; }
	bool Contains(T item);
	int Count() { return count; }
	bool Remove(T item);
private:
	void GrowArray();
};

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &other)
{
	length = other.length;
	count = other.count;
	items = new T[length];
	for (size_t i = 0; i < count; i++)
		items[i] = other.items[i];
}


template <typename T>
void ArrayList<T>::swap(ArrayList & other)
{
	swap(lenght, other.length);
	swap(count, other.count);
	swap(items, other.items);
}

template <typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList &other)
{
	ArrayList temp(other);
	swap(temp);
	return *this;
	// реализация с проверкой самоприсваивания
	//if (this != &other)
	//	ArrayList(other).swap(*this);
	//return *this;
}

template <typename T>
void ArrayList<T>::GrowArray()
{
	int newLength = length == 0 ? 4 : length << 1;
	T *newArray = new T[newLength];
	for (size_t i = 0; i < count; i++)
		newArray[i] = items[i];
	delete[] items;
	items = newArray;
	length = newLength;
}

template <typename T>
void ArrayList<T>::Insert(int index, T item)
{
	if (index >= count)
		throw exception();
	if (length == count)
		GrowArray();
	for (int i = count; i > index; i--)
		items[i] = items[i - 1];
	items[index] = item;
	count++;
}

template <typename T>
void ArrayList<T>::Add(T item)
{
	if (length == count)
		GrowArray();
	items[count++] = item;
}

template <typename T>
void ArrayList<T>::RemoveAt(int index)
{
	if (index >= count)
		throw exception();
	for (int i = index; i < count; i++)
		items[i] = items[i + 1];
	count--;
}

template <typename T>
bool ArrayList<T>::Remove(T item)
{
	for (size_t i = 0; i < count; i++)
	{
		if (items[i] == item)
		{
			RemoveAt(i);
			return true;
		}
	}
	return false;
}

template <typename T>
int ArrayList<T>::IndexOf(T item)
{
	for (size_t i = 0; i < count; i++)
	{
		if (items[i] == item)
			return i;
	}
	return -1;
}

template <typename T>
bool ArrayList<T>::Contains(T item)
{
	return IndexOf(item) != -1;
}

#endif // ARRAY_LIST_H_