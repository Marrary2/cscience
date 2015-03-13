/* 
 * File:   binary_array_heap.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 29, 2010, 5:11 AM
 */

#ifndef INCLUDED_cscience_pqueue__binary_array_heap_h
#define INCLUDED_cscience_pqueue__binary_array_heap_h

#include <algorithm>
#include <functional>
#include <cstddef>

namespace cscience {
namespace pqueue {

// TODO: make this class an adapter for a random access data structure (remove dtor...) and rename it to binary_heap_adapter
// TODO: make use of iterators instead of indexes

template <typename TValue, typename TRelation = std::less<TValue>>
struct binary_array_heap
{
	typedef TValue value_type;
	typedef size_t size_type;
	typedef TRelation order_relation;

private:
	value_type *heap;
	size_type length;
	size_type capacity;
	order_relation relation;

	void build_heap() {
		for(size_t i = length / 2; i--; ) {
			heapify_top_down(i);
		}
	}

	void heapify_top_down(size_type index) {
		// FIXME: Watch for overflow here if index is higher than MAX_UINT / 2
		for(size_t child, top = index; (child = (index * 2) + 1) < length; index = top) {
			if(relation(heap[child], heap[top])) {
				top = child;
			}

			if(++child < length && relation(heap[child], heap[top])) {
				top = child;
			}

			if(top == index) {
				break;
			}

			std::swap(heap[index], heap[top]);
		}
	}

	void heapify_bottom_up(size_type index) {
		while(index > 0) {
			size_t parent = (index - 1) / 2;

			if(!relation(heap[index], heap[parent])) {
				break;
			}

			std::swap(heap[index], heap[parent]);
			index = parent;
		}
	}

public:
	binary_array_heap(size_type capacity, order_relation relation = order_relation()):
		heap(0),
		length(0),
		capacity(capacity),
		relation(relation)
	{
		heap = new value_type[capacity];
	}

	binary_array_heap(value_type const *heap, size_type length, order_relation relation = order_relation()):
		heap(0),
		length(length),
		capacity(length),
		relation(relation)
	{
		heap = new value_type[length];

		std::copy(heap, heap + length, heap);

		build_heap();
	}

	~binary_array_heap() {
		delete [] heap;
	}

	void push(value_type const &value) {
		set(value, ++length);
	}

	void set(value_type const &value, size_type index = 0) {
		if(relation(heap[index], value)) {
			heap[index] = value;
			heapify_top_down(index);
		}
		else {
			heap[index] = value;
			heapify_bottom_up(index);
		}
	}

	void extract(size_type index = 0) {
		--length;

		std::swap(heap[index], heap[length]);

		heapify_top_down(index);
	}

	void pop(size_type index = 0) {
		--length;

		heap[index] = heap[length];

		heapify_top_down(index);
	}

	void clear() {
		length = 0;
	}

	value_type const &top() const {
		return heap[0];
	}

	value_type &top() {
		return heap[0];
	}

	size_type size() const {
		return length;
	}

	bool full() const {
		return length == capacity;
	}

	bool empty() const {
		return !length;
	}

	value_type const &operator [](size_type index) const {
		return heap[index];
	}

	value_type &operator [](size_type index) {
		return heap[index];
	}
};

} // namespace pqueue {
} // namespace cscience {

#endif	// INCLUDED_cscience_pqueue__binary_array_heap_h
