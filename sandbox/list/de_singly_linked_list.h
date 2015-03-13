/* 
 * File:   de_singly_linked_list.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 13, 2010, 4:34 PM
 */

#ifndef DE_SINGLY_LINKED_LIST_H
#    define	DE_SINGLY_LINKED_LIST_H

#include <list/singly_linked_node.h>

#include <cstddef>

namespace cscience {
namespace list {

template <typename TValue>
class de_singly_linked_list
{
public:
	typedef singly_linked_node<TValue> node_type;
	typedef typename node_type::value_type value_type;
	typedef size_t size_type;

private:
	node_type *m_head;
	node_type *m_tail;

public:
	de_singly_linked_list():
		m_head(0),
		m_tail(0)
	{
	}

	~de_singly_linked_list()
	{
		clear();
	}

	void add_before_head(value_type const &value)
	{
		node_type *node = new node_type(value);

		node->next = this->m_head;
		this->m_head = node;

		if(!this->m_tail)
		{
			this->m_tail = node;
		}
	}

	void add_after_tail(value_type const &value)
	{
		node_type *node = new node_type(value);

		if(this->m_tail)
		{
			this->m_tail->next = node;
		}
		else
		{
			this->m_head = node;
		}

		this->m_tail = node;
	}

	void insert_after(value_type const &value, node_type *where)
	{
		if(!where)
		{
			add_before_head(value);

			return;
		}

		node_type *node = new node_type(value);

		node->next = where->next;
		where->next = node;

		if(!node->next)
		{
			this->m_tail = node;
		}
	}

	bool insert_before(value_type const &value, node_type *where)
	{
		node_type *prev = 0;
		node_type *i = this->m_head;

		while(i)
		{
			if(i == where)
			{
				break;
			}

			prev = i;
			i = i->next;
		}

		if(i != where)
		{
			return false;
		}

		node_type *node = new node_type(value);

		node->next = where;

		if(!where)
		{
			this->m_tail = node;
		}

		if(prev)
		{
			prev->next = node;
		}
		else
		{
			this->m_head = node;
		}

		return true;
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

	bool remove_head()
	{
		if(!this->m_head)
		{
			return false;
		}

		node_type *node = this->m_head;

		this->m_head = node->next;

		if(!this->m_head)
		{
			this->m_tail = 0;
		}

		delete node;

		return true;
	}

	bool remove_tail()
	{
		remove_node(this->m_tail);
	}

	bool remove_node(node_type *node)
	{
		if(!node)
		{
			return false;
		}

		node_type *prev = 0;
		node_type *i = this->m_head;

		while(i)
		{
			if(i == node)
			{
				break;
			}

			prev = i;
			i = i->next;
		}

		if(i != node)
		{
			return false;
		}

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

		delete node;

		return true;
	}

	bool remove_value(value_type const &value)
	{
		node_type *prev = 0;
		node_type *node = this->m_head;

		while(node)
		{
			if(node->value == value)
			{
				break;
			}

			prev = node;
			node = node->next;
		}

		if(!node)
		{
			return false;
		}

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

		delete node;

		return true;
	}

	node_type *improved_find(value_type const &value, node_type *&prev)
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

	bool fast_remove(node_type *node, node_type *prev)
	{
		if(!node)
		{
			return false;
		}

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

		delete node;

		return true;
	}

	bool simpler_remove(value_type const &value)
	{
		node_type *prev;
		node_type *node = find(value, prev);

		return fast_remove(node, prev);
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
	}

	bool empty() const
	{
		return !this->m_head;
	}

	size_type size() const
	{
		size_type size = 0;

		for(node_type *i = this->m_head; i; i = i->next)
		{
			++size;
		}

		return size;
	}

	node_type *head()
	{
		return this->m_head;
	}

	node_type *tail()
	{
		return this->m_tail;
	}
};

} // namespace list {
} // namespace cscience {

#endif	/* DE_SINGLY_LINKED_LIST_H */
