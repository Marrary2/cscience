/* 
 * File:   doubly_linked_node.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 31, 2010, 1:28 AM
 */

#ifndef DOUBLY_LINKED_NODE_H
#    define	DOUBLY_LINKED_NODE_H

namespace cscience {
namespace list {

template <typename TValue>
struct doubly_linked_node
{
	typedef TValue value_type;

	doubly_linked_node(value_type const &value):
		value(value)
	{
	}

	TValue value;
	doubly_linked_node<value_type> *next;
	doubly_linked_node<value_type> *prev;
};

} // namespace list {
} // namespace cscience {

#endif	/* DOUBLY_LINKED_NODE_H */
