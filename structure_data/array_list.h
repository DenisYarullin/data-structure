#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include "iterator.h"
#include <algorithm>
#include <exception>
#include <vld.h>


template <typename T>
class ArrayList
{
private:
	int length;
	int count;
	T *items;
public:
	typedef Iterator<T> iterator;
	typedef size_t size_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	ArrayList() : length(0), count(0), items(new T[0]) {}
	ArrayList(int length_) : length(length_), count(0)
	{
		if (length < 0)
		{
			throw std::length_error("length");
		}
		items = new T[length];
		std::fill(items, items + length, T());
		
	}
	ArrayList(const ArrayList &other);
	ArrayList &operator=(const ArrayList &other);
	T &operator[](int index) { return items[index]; }
	const T &operator[](int index) const { return items[index]; }
	~ArrayList() { delete[] items; }
	int IndexOf(T item);
	void Insert(int index, T item);
	void RemoveAt(int index);
	void Add(T item);
	void Clear() { count = 0; lenght = 0; delete [] items; }
	bool Contains(T item);
	int Count() { return count; }
	int Capacity() { return length; }
	bool Remove(T item);

	Iterator<T> begin()
	{
		return Iterator<T>(items);
	}

	Iterator<T> end()
	{
		return Iterator<T>(items + count);
	}
private:
	void swap(ArrayList &other);
	void GrowArray();
};

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &other)
{
	items = new T[other.length];
	std::copy(other.items, other.items + other.count, items);

	length = other.length;
	count = other.count;
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
	std::copy(items, items + count, newArray);

	delete[] items;
	items = newArray;
	length = newLength;
}

template <typename T>
void ArrayList<T>::Insert(int index, T item)
{
	if (index >= count)
		throw std::exception("wrong index");
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
		throw std::exception("wrong index");
	for (int i = index; i < count; i++)
		if (i + 1 < count)
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