/* 
 * File:   static_array.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on January 4, 2011, 4:17 AM
 */

#ifndef STATIC_ARRAY_H
#    define	STATIC_ARRAY_H

#include <cstddef>

namespace cscience {
namespace array {

template <typename TValue>
class static_array
{
public:
	typedef TValue value_type;
	typedef size_t size_type;

private:
	value_type *m_array;
	size_type m_size;
	size_type m_capacity;

public:
	static_array(size_type capacity = 0):
		m_array(0),
		m_size(0),
		m_capacity(capacity)
	{
		if(this->m_capacity)
		{
			this->m_array = new value_type[this->m_capacity];
		}
	}

	~static_array()
	{
		delete [] this->m_array;
	}

	void push_back(value_type const &value)
	{
		this->m_array[this->m_size++] = value;
	}

	void pop_back()
	{
		--this->m_size;
	}

	void insert(size_type index, value_type const &value)
	{
		for(size_type i = this->m_size - 1; i > index; --i)
		{
			this->m_array[i] = this->m_array[i - 1];
		}

		this->m_array[index] = value;
	}

	void erase(size_type index)
	{
		erase(index, index + 1);
	}

	void erase(size_type offset, size_type end)
	{
		size_type gap = end - offset;

		for(size_type i = end; i < this->m_size; ++i)
		{
			this->m_array[i - gap] = this->m_array[i];
		}

		this->m_size -= gap;
	}

	value_type const &front() const
	{
		return this->m_array[0];
	}

	value_type &front()
	{
		return this->m_array[0];
	}

	value_type const &back() const
	{
		return this->m_array[this->m_size - 1];
	}

	value_type &back()
	{
		return this->m_array[this->m_size - 1];
	}

	void clear()
	{
		this->m_size = 0;
	}

	size_type size() const
	{
		return this->m_size;
	}

	size_type capacity() const
	{
		return this->m_capacity;
	}

	bool full() const
	{
		return this->m_size == this->m_capacity;
	}

	bool empty() const
	{
		return !this->m_size;
	}

	value_type const &operator [](size_type index) const
	{
		return this->m_array[index];
	}

	value_type &operator [](size_type index)
	{
		return this->m_array[index];
	}

	operator value_type const *() const
	{
		return this->m_array;
	}

	operator value_type *()
	{
		return this->m_array;
	}
};

} // namespace array {
} // namespace cscience {

#endif	/* STATIC_ARRAY_H */
