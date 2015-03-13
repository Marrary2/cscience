/*
 * binary_tree_traverser.h
 *
 *  Created on: Sep 5, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_tree__binary_tree_traverser_h
#define INCLUDED_cscience_tree__binary_tree_traverser_h

#include <stack>
#include <queue>

#include <cassert>

namespace cscience {
namespace tree {
namespace internal {

template <typename walker_type, typename stack_type>
class base_dfs_traverser {
protected:
	stack_type stack;

public:
	typedef typename walker_type::node_type node_type;

	explicit operator node_type() const {
		assert(!stack.empty());

		return stack.top();
	}

	explicit operator bool() const {
		return !stack.empty();
	}

	bool operator !() const {
		return stack.empty();
	}

	bool operator ==(base_dfs_traverser const &other) const {
		return stack == other.stack;
	}

	bool operator !=(base_dfs_traverser const &other) const {
		return stack != other.stack;
	}

	node_type const &operator *() const {
		assert(!stack.empty());

		return *stack.top();
	}

	node_type &operator *() {
		assert(!stack.empty());

		return *stack.top();
	}

	node_type const *operator ->() const {
		assert(!stack.empty());

		return stack.top();
	}

	node_type *operator ->() {
		assert(!stack.empty());

		return stack.top();
	}
};

template <typename walker_type, typename queue_type>
class base_bfs_traverser {
protected:
	queue_type queue;

public:
	typedef typename walker_type::node_type node_type;

	explicit operator node_type() const {
		assert(!queue.empty());

		return queue.top();
	}

	explicit operator bool() const {
		return !queue.empty();
	}

	bool operator !() const {
		return queue.empty();
	}

	bool operator ==(base_bfs_traverser const &other) const {
		return queue == other.queue;
	}

	bool operator !=(base_bfs_traverser const &other) const {
		return queue != other.queue;
	}

	node_type const &operator *() const {
		return *queue.front();
	}

	node_type &operator *() {
		return *queue.front();
	}

	node_type const *operator ->() const {
		return queue.front();
	}

	node_type *operator ->() {
		return queue.front();
	}
};

} // namespace internal {

template <typename walker_type, typename stack_type = std::stack<walker_type>>
struct binary_tree_in_order_traverser:
	public internal::base_dfs_traverser<walker_type, stack_type>
{
	binary_tree_in_order_traverser(walker_type walker) {
		if(!walker) {
			return;
		}

		do {
			this->stack.push(walker);
		} while(walker.walk_left());
	}

	binary_tree_in_order_traverser &operator ++() {
		assert(!this->stack.empty());

		auto child = this->stack.top().right();
		this->stack.pop();

		while(child) {
			this->stack.push(child);
			child.walk_left();
		}

		return *this;
	}
};

template <typename walker_type, typename stack_type = std::stack<walker_type>>
struct binary_tree_pre_order_traverser:
	public internal::base_dfs_traverser<walker_type, stack_type>
{
	binary_tree_pre_order_traverser(walker_type const &walker) {
		if(walker) {
			this->stack.push(walker);
		}
	}

	binary_tree_pre_order_traverser &operator ++() {
		assert(!this->stack.empty());

		auto walker = this->stack.top();
		this->stack.pop();

		if(walker.has_right()) {
			this->stack.push(walker.right());
		}

		if(walker.has_left()) {
			this->stack.push(walker.left());
		}

		return *this;
	}
};

template <typename walker_type, typename stack_type = std::stack<walker_type>, typename flag_stack = std::stack<bool>>
class binary_tree_post_order_traverser:
	public internal::base_dfs_traverser<walker_type, stack_type>
{
	flag_stack flags;

public:
	binary_tree_post_order_traverser(walker_type walker) {
		while(walker) {
			do {
				this->stack.push(walker);
				this->flags.push(walker.has_right());

				assert(this->stack.size() == this->flags.size());
			} while(walker.walk_left());

			if(this->flags.top()) {
				this->flags.top() = false;

				walker = this->stack.top().right();
			}
		}
	}

	binary_tree_post_order_traverser &operator ++() {
		assert(!this->stack.empty());
		assert(!this->flags.empty());

		this->stack.pop();
		this->flags.pop();

		assert(this->stack.size() == this->flags.size());

		if(this->stack.empty() || !this->flags.top()) {
			return *this;
		}

		assert(!this->stack.empty());

		for(auto walker = this->stack.top().left(); walker; ) {
			do {
				this->stack.push(walker);
				this->flags.push(walker.has_right());

				assert(this->stack.size() == this->flags.size());
			} while(walker.walk_left());

			if(this->flags.top()) {
				this->flags.top() = false;

				walker = this->stack.top().right();
			}
		}

		return *this;
	}
};

template <typename walker_type, typename queue_type = std::queue<walker_type>>
struct binary_tree_level_order_traverser:
	public internal::base_bfs_traverser<walker_type, queue_type>
{
	binary_tree_level_order_traverser(walker_type const &walker) {
		if(walker) {
			this->queue.push(walker);
		}
	}

	binary_tree_level_order_traverser &operator ++() {
		assert(!this->queue.empty());

		auto walker = this->queue.front();
		this->queue.pop();

		this->queue.push(walker.left());
		this->queue.push(walker.right());

		return *this;
	}
};

} // namespace tree {
} // namespace cscience {

#endif // INCLUDED_cscience_tree__binary_tree_traverser_h
