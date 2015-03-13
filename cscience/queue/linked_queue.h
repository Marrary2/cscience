/* 
 * File:   linked_queue.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 30, 2010, 3:35 AM
 */

#ifndef LINKED_QUEUE_H
#    define	LINKED_QUEUE_H

#include <cscience/list/singly_linked_list.h>

namespace cscience {
namespace queue {

template <typename TValue>
class linked_queue
{
private:
	typedef cscience::list::singly_linked_list<TValue> list_type;

public:
	typedef typename list_type::value_type value_type;
	typedef typename list_type::size_type size_type;

private:
	list_type m_queue;

public:
	void enqueue(value_type const &value)
	{
		this->m_queue.push_back();
	}

	void dequeue()
	{
		this->m_queue.pop_front();
	}

	value_type const &front() const
	{
		return this->m_queue.front();
	}

	value_type &front()
	{
		return this->m_queue.front();
	}

	void clear()
	{
		this->m_queue.clear();
	}

	bool empty() const
	{
		return this->m_queue.empty();
	}

	size_type size() const
	{
		return this->m_queue.size();
	}
};

} // namespace cscience {
} // namespace queue {

#endif	/* LINKED_QUEUE_H */
