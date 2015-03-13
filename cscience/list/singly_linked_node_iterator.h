/* 
 * File:   singly_linked_node_iterator.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 20, 2010, 2:48 AM
 */

#ifndef SINGLY_LINKED_NODE_ITERATOR_H
#    define	SINGLY_LINKED_NODE_ITERATOR_H

namespace cscience {
namespace list {

template <typename TNode>
class singly_linked_node_iterator
{
public:
	typedef TNode node_type;
	typedef typename node_type::value_type value_type;

private:
	node_type *m_prev;
	node_type *m_node;

public:
	singly_linked_node_iterator(node_type *node, node_type *prev = 0):
		m_node(node),
		m_prev(prev)
	{
	}

	singly_linked_node_iterator(singly_linked_node_iterator<TNode> const &iterator):
		m_node(iterator.m_node),
		m_prev(iterator.m_prev)
	{
	}

	singly_linked_node_iterator<TNode> &operator ++(int)
	{
		return singly_linked_node_iterator<TNode>(this->m_node->next, this->m_node);
	}

	singly_linked_node_iterator<TNode> &operator ++()
	{
		this->m_prev = this->m_node;
		this->m_node = this->m_node->next;

		return *this;
	}

	singly_linked_node_iterator<TNode> &operator =(singly_linked_node_iterator<TNode> const &iterator)
	{
		this->m_node = iterator.m_node;
		this->m_prev = iterator.m_prev;

		return *this;
	}

	bool operator !=(singly_linked_node_iterator<TNode> const &iterator) const
	{
		return this->m_node != iterator.m_node
			|| this->m_prev != iterator.m_prev;
	}

	bool operator ==(singly_linked_node_iterator<TNode> const &iterator) const
	{
		return this->m_node == iterator.m_node
			&& this->m_prev == iterator.m_prev;
	}

	bool operator !() const
	{
		return !this->m_node;
	}

	operator bool() const
	{
		return this->m_node != 0;
	}
};

} // namespace list {
} // namespace cscience {

#endif	/* SINGLY_LINKED_NODE_ITERATOR_H */
