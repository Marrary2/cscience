/*
 * binary_tree_walker.h
 *
 *  Created on: Sep 5, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_tree__binary_tree_walker_h
#define INCLUDED_cscience_tree__binary_tree_walker_h

#include <stack>
#include <vector>

#include <cassert>

// TODO: Add move semantics to the walker classes
// TODO: Clean up code with traits classes

namespace cscience {
namespace tree {

template <typename node_t, node_t *(node_t::*left_getter)(), node_t *(node_t::*right_getter)()>
struct forward_binary_tree_walker {
	typedef node_t node_type;

private:
	node_type *node;
	node_type *parent;
	bool isRight;

	forward_binary_tree_walker(node_type *node, node_type *parent, bool isRight):
		node(node),
		parent(parent),
		isRight(isRight)
	{
		assert(left_getter);
		assert(right_getter);
	}

	typedef node_t *(node_t::*node_getter)();
	typedef void(node_t::*node_setter)(node_t *);

	template <node_getter target_getter, node_getter source_getter, node_setter target_setter, node_setter source_setter>
	void rotate(bool isTargetSideChild) {
		auto arm = node;
		assert(arm);

		auto pivot = (arm->*source_getter)();
		assert(pivot);

		(arm->*source_setter)((pivot->*target_getter)());
		pivot->*target_setter(arm);

		if(parent) {
			if(isTargetSideChild) {
				(parent->*target_setter)(pivot);
			}
			else {
				(parent->*source_setter)(pivot);
			}
		}

		node = pivot;
	}

public:
	forward_binary_tree_walker(node_type *node):
		node(node),
		parent(0),
		isRight(false)
	{
		assert(left_getter);
		assert(right_getter);
	}

	forward_binary_tree_walker(forward_binary_tree_walker const &) = default;

	node_type *get_left() const {
		assert(node);

		return (node->*left_getter)();
	}

	node_type *get_right() const {
		assert(node);

		return (node->*right_getter)();
	}

	forward_binary_tree_walker left() const {
		return forward_binary_tree_walker(get_left(), node, false);
	}

	forward_binary_tree_walker right() const {
		return forward_binary_tree_walker(get_right(), node, true);
	}

	bool has_left() const {
		return get_left();
	}

	bool has_right() const {
		return get_right();
	}

	bool is_root() const {
		return !parent;
	}

	bool is_left() const {
		return !isRight;
	}

	bool is_right() const {
		return isRight;
	}

	bool walk_left() {
		assert(node);

		parent = node;
		node = get_left();
		isRight = false;

		return bool(*this);
	}

	bool walk_right() {
		assert(node);

		parent = node;
		node = get_right();
		isRight = true;

		return bool(*this);
	}

	template <node_setter left_setter, node_setter right_setter>
	void rotate_left() {
		rotate<left_getter, right_getter, left_setter, right_setter>(
			is_left()
		);
	}

	template <node_setter left_setter, node_setter right_setter>
	void rotate_right() {
		rotate<right_getter, left_getter, right_setter, left_setter>(
			is_right()
		);
	}

	explicit operator node_type *() const {
		return node;
	}

	explicit operator bool() const {
		return node;
	}

	bool operator !() const {
		return !node;
	}

	bool operator ==(forward_binary_tree_walker const &other) const {
		return node == other.node;
	}

	bool operator !=(forward_binary_tree_walker const &other) const {
		return node != other.node;
	}

	node_type &operator *() const {
		assert(node);

		return *node;
	}

	node_type *operator ->() const {
		return node;
	}
};

template <
	typename node_t,
	node_t *(node_t::*left_getter)(),
	node_t *(node_t::*right_getter)(),
	typename node_stack = std::stack<node_t *>,
	typename flag_stack = std::stack<bool, std::vector<bool>>
>
struct two_way_binary_tree_walker {
	typedef node_t node_type;

private:
	node_stack stack;
	flag_stack isRight;

	typedef node_t *(node_t::*node_getter)();
	typedef void(node_t::*node_setter)(node_t *);

	template <node_getter target_getter, node_getter source_getter, node_setter target_setter, node_setter source_setter>
	void rotate(bool isTargetSideChild) {
		assert(!stack.empty());

		auto arm = stack.top();
		assert(arm);
		stack.pop();

		auto pivot = (arm->*source_getter)();
		assert(pivot);

		(arm->*source_setter)((pivot->*target_getter)());
		pivot->*target_setter(arm);

		if(!stack.empty()) {
			if(isTargetSideChild) {
				(stack.top()->*target_setter)(pivot);
			}
			else {
				(stack.top()->*source_setter)(pivot);
			}
		}

		stack.push(pivot);

		return *this;
	}

public:
	two_way_binary_tree_walker(node_type *node) {
		assert(left_getter);
		assert(right_getter);

		stack.push(node);
	}

	two_way_binary_tree_walker(two_way_binary_tree_walker const &) = default;

	node_type *get_left() const {
		assert(!stack.empty());
		assert(stack.top());

		return (stack.top()->*left_getter)();
	}

	node_type *get_right() const {
		assert(!stack.empty());
		assert(stack.top());

		return (stack.top()->*right_getter)();
	}

	two_way_binary_tree_walker left() const {
		auto walker = *this;

		walker.walk_left();

		return walker;
	}

	two_way_binary_tree_walker right() const {
		auto walker = *this;

		walker.walk_left();

		return walker;
	}

	two_way_binary_tree_walker parent() const {
		auto walker = *this;

		walker.walk_back();

		return walker;
	}

	bool has_left() const {
		return get_left();
	}

	bool has_right() const {
		return get_right();
	}

	bool is_root() const {
		return stack.size() == 1;
	}

	bool is_left() const {
		return !(isRight.empty() || isRight.top());
	}

	bool is_right() const {
		return !isRight.empty() && isRight.top();
	}

	bool walk_left() {
		assert(!stack.empty());
		assert(stack.top());

		stack.push(get_left());
		isRight.push(false);

		assert(stack.size() - 1 == isRight.size());

		return *this;
	}

	bool walk_right() {
		assert(!stack.empty());
		assert(stack.top());

		stack.push(get_right());
		isRight.push(true);

		assert(stack.size() - 1 == isRight.size());

		return *this;
	}

	bool walk_back() {
		assert(!stack.empty());

		stack.pop();

		if(!isRight.empty()) {
			isRight.pop();
		}

		assert(stack.empty() ? isRight.empty() : stack.size() - 1 == isRight.size());

		return *this;
	}

	template <node_setter left_setter, node_setter right_setter>
	void rotate_left() {
		rotate<left_getter, right_getter, left_setter, right_setter>(
			is_left()
		);
	}

	template <node_setter left_setter, node_setter right_setter>
	void rotate_right() {
		rotate<right_getter, left_getter, right_setter, left_setter>(
			is_right()
		);
	}

	explicit operator node_type *() const {
		assert(!stack.empty());

		return stack.top();
	}

	explicit operator bool() const {
		return !stack.empty() && stack.top();
	}

	bool operator !() const {
		return stack.empty() || !stack.top();
	}

	bool operator ==(two_way_binary_tree_walker const &other) const {
		return stack == other.stack;
	}

	bool operator !=(two_way_binary_tree_walker const &other) const {
		return stack != other.stack;
	}

	node_type &operator *() const {
		assert(!stack.empty());
		assert(stack.top());

		return *stack.top();
	}

	node_type *operator ->() const {
		assert(!stack.empty());
		assert(stack.top());

		return stack.top();
	}
};

} // namespace tree {
} // namespace cscience {

#endif // INCLUDED_cscience_tree__binary_tree_walker_h
