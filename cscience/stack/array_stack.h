/* 
 * File:   array_stack.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 30, 2010, 3:35 AM
 */

#ifndef ARRAY_STACK_H
#    define	ARRAY_STACK_H

#include <cstddef>

namespace cscience {
namespace stack {

template <typename TValue>
class array_stack
{
public:
	typedef TValue value_type;
	typedef size_t size_type;

private:
	value_type *m_stack;
	size_type m_size;
	size_type m_capacity;

public:
	array_stack(size_type capacity):
		m_stack(0),
		m_size(0),
		m_capacity(capacity)
	{
		this->m_stack = new value_type[this->m_capacity];
	}

	~array_stack()
	{
		delete [] this->m_stack;
	}

	void push(value_type const &value)
	{
		this->m_stack[this->m_size++] = value;
	}

	void pop()
	{
		--this->m_size;
	}

	value_type const &top() const
	{
		return this->m_stack[this->m_size - 1];
	}

	value_type &top()
	{
		return this->m_stack[this->m_size - 1];
	}

	void clear()
	{
		this->m_size = 0;
	}

	bool full() const
	{
		return this->m_size == this->m_capacity;
	}

	bool empty() const
	{
		return !this->m_size;
	}

	size_type size() const
	{
		return this->m_size;
	}
};

} // namespace stack {
} // namespace stack {

#endif	/* ARRAY_STACK_H */
