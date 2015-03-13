/* 
 * File:   stack_adapter.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 30, 2010, 3:36 AM
 */

#ifndef STACK_ADAPTER_H
#    define	STACK_ADAPTER_H

namespace cscience {
namespace stack {

template <typename TContainer>
class stack_adapter
{
private:
	typedef TContainer container_type;

public:
	typedef typename container_type::value_type value_type;
	typedef typename container_type::size_type size_type;

private:
	container_type m_stack;

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

#endif	/* STACK_ADAPTER_H */
