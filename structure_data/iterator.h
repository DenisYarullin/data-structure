#ifndef ITERATOR_H_
#define ITERATOR_H_


#include <iterator>

template <typename T>
class Iterator
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::random_access_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;
	typedef std::ptrdiff_t distance_type;

	Iterator(pointer current_) : current(current_)
	{
	}

	~Iterator() { delete current; }

	Iterator &operator ++()
	{
		++current;
		return *this;
	}

	Iterator operator ++(int)
	{
		Iterator temp(current);
		++current;
		return temp;
		// return Iterator(value++);
	}

	Iterator &operator --()
	{
		--current;
		return *this;
	}

	Iterator &operator --(int)
	{
		Iterator temp(current);
		--current;
		return temp;
		// return Iterator(value++);
	}

	reference operator *()
	{
		return *current;
	}

	pointer operator ->()
	{
		return current;
	}

	bool operator ==(const Iterator &other)
	{
		return current == other.current;
	}

	bool operator !=(const Iterator &other)
	{
		return !(*this == other);
	}

	bool operator < (const Iterator &other)
	{
		return current < other.current;
	}

	difference_type operator - (const Iterator &other)
	{
		return current - other.current;
	}

	Iterator operator -(distance_type value)
	{
		return Iterator(current - value);
	}

	Iterator operator +(distance_type value)
	{
		return Iterator(current + value);
	}

private:
	Iterator(const Iterator &other) = delete;
	Iterator &operator =(const Iterator &other) = delete;
private:
	pointer current;
};

#endif // ITERATOR_H_ 