/* 
 * File:   singly_linked_node.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 9, 2010, 12:59 AM
 */

#ifndef SINGLY_LINKED_NODE_H
#    define	SINGLY_LINKED_NODE_H

namespace cscience {
namespace list {

template <typename TValue>
struct singly_linked_node
{
	typedef TValue value_type;

	singly_linked_node(value_type const &value):
		value(value)
	{
	}

	TValue value;
	singly_linked_node<value_type> *next;
};

} // namespace list {
} // namespace cscience {

#endif	/* SINGLY_LINKED_NODE_H */
