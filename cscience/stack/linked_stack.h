/* 
 * File:   linked_stack.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 30, 2010, 3:36 AM
 */

#ifndef LINKED_STACK_H
#    define	LINKED_STACK_H

#include <cscience/list/singly_linked_list.h>

namespace cscience {
namespace stack {

template <typename TValue>
class linked_stack
{
private:
	typedef cscience::list::singly_linked_list<TValue> list_type;

public:
	typedef typename list_type::value_type value_type;
	typedef typename list_type::size_type size_type;

private:
	list_type m_stack;

public:
	void push(value_type const &value)
	{
		this->m_stack.push_front();
	}

	void pop()
	{
		this->m_stack.pop_front();
	}

	value_type const &top() const
	{
		return this->m_stack.front();
	}

	value_type &top()
	{
		return this->m_stack.front();
	}

	void clear()
	{
		this->m_stack.clear();
	}

	bool empty() const
	{
		return this->m_stack.empty();
	}

	size_type size() const
	{
		return this->m_stack.size();
	}
};

} // namespace stack {
} // namespace stack {

#endif	/* LINKED_STACK_H */
