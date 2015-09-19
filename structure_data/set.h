#ifndef SET_H_
#define SET_H_

#include <vector>
#include <algorithm>
#include <initializer_list>

using std::vector;

template <typename T>
class Set
{
private:
	vector<T> items;
public:
	Set() {}
	Set(std::initializer_list<T> items_) : items(items_) {}
	void Add(T item);
	void AddRange(std::initializer_list<T> items_);
	bool Remove(T item);
	bool Contains(T item);
	int Count() { return items.size() };
	Set *Union(Set &other);
	Set *Intersection(Set &other);
	Set *Difference(Set &other);
	Set *SymmetricDifference(Set &other);
	vector<T> & Items() { return items; }
};

template <typename T>
void Set<T>::Add(T item)
{
	if (Contains(item))
	{
		throw exception("Item is already exists in Set");
	}
	items.push_back(item);
	std::sort(items.begin(), items.end());
}

template <typename T>
void Set<T>::AddRange(std::initializer_list<T> items_)
{
	for (auto item : items_)
	{
		Add(item);
	}
}

template <typename T>
bool Set<T>::Remove(T item)
{
	vector<T>::iterator c = items.erase(std::remove(items.begin(), items.end(), item), items.end());
	return c != items.end();
}

template <typename T>
bool Set<T>::Contains(T item)
{
	vector<T>::iterator c = std::find(items.cbegin(), items.cend(), item);
	return c != items.end();
}

template <typename T>
Set<T> * Set<T>::Union(Set &other)
{
	Set *result = new Set(items);
	for (auto item : other.Items())
	{
		if (!Contains(item))
		{
			result->Add(item);
		}
	}
	return result;
}

template <typename T>
Set<T> * Set<T>::Intersection(Set &other)
{
	Set *result = new Set();
	for (auto item : items)
	{
		if (other.Contains(item))
		{
			result->Add(item);
		}
	}
	return result;
}

template <typename T>
Set<T> * Set<T>::Difference(Set &other)
{
	Set *result = new Set(items);

	for (auto item : other.Items())
	{
		result->Remove(item);
	}
	return result;
}

template <typename T>
Set<T> * Set<T>::SymmetricDifference(Set &other)
{
	Set *union_ = Union(other);
	Set *intersection_ = Intersection(other);
	Set *symmetricDifference = union_->Difference(intersection_);

	delete union_;
	delete intersection_;

	return symmetricDifference;
}


#endif // SET_H_