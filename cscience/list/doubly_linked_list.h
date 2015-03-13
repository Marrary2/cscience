/* 
 * File:   doubly_linked_list.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 31, 2010, 1:28 AM
 */

#ifndef DOUBLY_LINKED_LIST_H
#    define	DOUBLY_LINKED_LIST_H

#include <cscience/list/doubly_linked_node.h>

#include <cstddef>

namespace cscience {
namespace list {

template <typename TValue>
class doubly_linked_list
{
public:
	typedef doubly_linked_node<TValue> node_type;
	typedef typename node_type::value_type value_type;
	typedef size_t size_type;

private:
	node_type *m_head;
	node_type *m_tail;
	size_type m_size;

public:
	doubly_linked_list():
		m_head(0),
		m_tail(0),
		m_size(0)
	{
	}

	~doubly_linked_list()
	{
		clear();
	}

	void push_front(value_type const &value)
	{
		node_type *node = new node_type(value);

		node->next = this->m_head;
		node->prev = 0;

		if(this->m_head)
		{
			this->m_head->prev = node;
		}
		else
		{
			this->m_tail = node;
		}

		this->m_head = node;
		++this->m_size;
	}

	void push_back(value_type const &value)
	{
		node_type *node = new node_type(value);

		node->next = 0;
		node->prev = this->m_tail;

		if(this->m_tail)
		{
			this->m_tail->next = node;
		}
		else
		{
			this->m_head = node;
		}

		this->m_tail = node;
		++this->m_size;
	}

	// inserts before node 'where'
	void insert(value_type const &value, node_type *where)
	{
		if(!where)
		{
			push_back(value);

			return;
		}

		node_type *node = new node_type(value);

		node->next = where;
		node->prev = where->prev;

		where->prev = node;

		if(!node->prev)
		{
			this->m_head = node;
		}

		++this->m_size;
	}

	// adds after node 'where'
	void add(value_type const &value, node_type *where)
	{
		if(!where)
		{
			push_front(value);

			return;
		}

		node_type *node = new node_type(value);

		node->next = where->next;
		node->prev = where;

		where->next = node;

		if(!node->next)
		{
			this->m_tail = node;
		}

		++this->m_size;
	}

	node_type *find(value_type const &value)
	{
		for(node_type *i = this->m_head; i; i = i->next)
		{
			if(i->value == value)
			{
				return i;
			}
		}

		return 0;
	}

	node_type *rfind(value_type const &value)
	{
		for(node_type *i = this->m_tail; i; i = i->prev)
		{
			if(i->value == value)
			{
				return i;
			}
		}

		return 0;
	}

	void pop_front()
	{
		node_type *node = this->m_head;

		this->m_head = this->m_head->next;

		if(this->m_head)
		{
			this->m_head->prev = 0;
		}

		delete node;
		--this->m_size;
	}

	void pop_back()
	{
		node_type *node = this->m_tail;

		this->m_tail = this->m_tail->prev;

		if(this->m_tail)
		{
			this->m_tail->next = 0;
		}

		delete node;
		--this->m_size;
	}

	void remove(node_type *node)
	{
		if(node->prev)
		{
			node->prev->next = node->next;
		}

		if(node->next)
		{
			node->next->prev = node->prev;
		}

		delete node;
		--this->m_size;
	}

	void remove(value_type const &value)
	{
		node_type *node = find(value);

		if(node)
		{
			remove(node);
		}
	}

	void clear()
	{
		for(node_type *i = this->m_head, *next; i; i = next)
		{
			next = i->next;

			delete i;
		}

		this->m_head = 0;
		this->m_tail = 0;
		this->m_size = 0;
	}

	node_type const *front() const
	{
		return this->m_head;
	}

	node_type *front()
	{
		return this->m_head;
	}

	node_type const *back() const
	{
		return this->m_tail;
	}

	node_type *back()
	{
		return this->m_tail;
	}

	bool empty() const
	{
		return !this->m_head;
	}

	size_type size() const
	{
		return this->m_size;
	}
};

} // namespace list {
} // namespace cscience {

#endif	/* DOUBLY_LINKED_LIST_H */
