/*
 * binary_tree.h
 *
 *  Created on: Sep 2, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_tree__binary_tree_h
#define INCLUDED_cscience_tree__binary_tree_h

#include "binary_tree_walker.h"
#include "binary_tree_traverser.h"

#include <cassert>

namespace cscience {
namespace tree {

template <typename value_type>
class linked_binary_tree {
	linked_binary_tree *left;
	linked_binary_tree *right;
	value_type value;

	linked_binary_tree *get_left() { return left; }
	linked_binary_tree *get_right() { return right; }
	void set_left(linked_binary_tree *child) { left = child; }
	void set_right(linked_binary_tree *child) { right = child; }

	typedef forward_binary_tree_walker<linked_binary_tree, &linked_binary_tree::get_left, &linked_binary_tree::get_right> forward_walker;
	typedef forward_binary_tree_walker<linked_binary_tree, &linked_binary_tree::get_left, &linked_binary_tree::get_right> reverse_forward_walker;

	typedef two_way_binary_tree_walker<linked_binary_tree, &linked_binary_tree::get_left, &linked_binary_tree::get_right> two_way_walker;
	typedef two_way_binary_tree_walker<linked_binary_tree, &linked_binary_tree::get_left, &linked_binary_tree::get_right> reverse_two_way_walker;

public:
	linked_binary_tree(value_type const &value, linked_binary_tree *left = 0, linked_binary_tree *right = 0):
		left(left),
		right(right),
		value(value)
	{
	}

	~linked_binary_tree() {
		delete left;
		delete right;
	}

	linked_binary_tree *insert_left(value_type const &value) {
		return (left = new linked_binary_tree(value, left, 0));
	}

	linked_binary_tree *insert_right(value_type const &value) {
		return (right = new linked_binary_tree(value, 0, right));
	}

	void delete_left() {
		delete left;
		left = 0;
	}

	void delete_right() {
		delete right;
		right = 0;
	}

	template <typename walker_type = forward_walker>
	walker_type walker() { return this; }

	template <typename walker_type = forward_walker>
	binary_tree_in_order_traverser<walker_type> in_begin() { return walker_type(this); }
	template <typename walker_type = forward_walker>
	binary_tree_in_order_traverser<walker_type> in_end() { return walker_type(0); }

	template <typename walker_type = forward_walker>
	binary_tree_pre_order_traverser<walker_type> pre_begin() { return walker_type(this); }
	template <typename walker_type = forward_walker>
	binary_tree_pre_order_traverser<walker_type> pre_end() { return walker_type(0); }

	template <typename walker_type = forward_walker>
	binary_tree_post_order_traverser<walker_type> post_begin() { return walker_type(this); }
	template <typename walker_type = forward_walker>
	binary_tree_post_order_traverser<walker_type> post_end() { return walker_type(0); }

	template <typename walker_type = forward_walker>
	binary_tree_level_order_traverser<walker_type> level_begin() { return walker_type(this); }
	template <typename walker_type = forward_walker>
	binary_tree_level_order_traverser<walker_type> level_end() { return walker_type(0); }

	value_type const &operator *() const {
		return value;
	}

	value_type &operator *() {
		return value;
	}
};

} // namespace tree {
} // namespace cscience {

#endif // INCLUDED_cscience_tree__binary_tree_h
