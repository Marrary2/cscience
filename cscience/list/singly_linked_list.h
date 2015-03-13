/* 
 * File:   singly_linked_list.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 13, 2010, 9:14 PM
 */

#ifndef SINGLY_LINKED_LIST_H
#    define	SINGLY_LINKED_LIST_H

#include <cscience/list/singly_linked_node.h>

#include <cstddef>

namespace cscience {
namespace list {

template <typename TValue>
class singly_linked_list
{
public:
	typedef singly_linked_node<TValue> node_type;
	typedef typename node_type::value_type value_type;
	typedef size_t size_type;

private:
	node_type *m_head;
	node_type *m_tail;
	size_type m_size;

public:
	singly_linked_list():
		m_head(0),
		m_tail(0),
		m_size(0)
	{
	}

	~singly_linked_list()
	{
		clear();
	}

	void push_front(value_type const &value)
	{
		node_type *node = new node_type(value);

		node->next = this->m_head;
		this->m_head = node;

		if(!this->m_tail)
		{
			this->m_tail = node;
		}

		++this->m_size;
	}

	void push_back(value_type const &value)
	{
		node_type *node = new node_type(value);

		node->next = 0;

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
	bool insert(value_type const &value, node_type const *where)
	{
		if(!where)
		{
			push_back(value);

			return true;
		}

		node_type *prev = find_prev(where);
		node_type *node = new node_type(value);

		node->next = where;

		if(prev)
		{
			prev->next = node;
		}
		else
		{
			this->m_head = node;
		}

		++this->m_size;

		return true;
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

	node_type *find(value_type const &value, node_type *&prev)
	{
		prev = 0;

		for(node_type *i = this->m_head; i; )
		{
			if(i->value == value)
			{
				return i;
			}

			prev = i;
			i = i->next;
		}

		return 0;
	}

	node_type *find_prev(node_type const *node)
	{
		if(!node)
		{
			return this->m_tail;
		}

		for(node_type *i = this->m_head, *prev = 0; i; )
		{
			if(i == node)
			{
				return prev;
			}

			prev = i;
			i = i->next;
		}

		return 0;
	}

	void pop_front()
	{
		node_type *node = this->m_head;

		this->m_head = node->next;

		if(!this->m_head)
		{
			this->m_tail = 0;
		}

		delete node;

		--this->m_size;
	}

	void pop_back()
	{
		remove(this->m_tail);
	}

	void remove(node_type *node, node_type *prev)
	{
		if(!node->next)
		{
			this->m_tail = prev;
		}

		if(prev)
		{
			prev->next = node->next;
		}
		else
		{
			this->m_head = node->next;
		}

		--this->m_size;

		delete node;
	}

	void remove(node_type *node)
	{
		remove(node, find_prev(node));
	}

	void remove(value_type const &value)
	{
		node_type *prev;
		node_type *node = find(value, prev);

		remove(node, prev);
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

#endif	/* SINGLY_LINKED_LIST_H */
