/* 
 * File:   circular_array_queue.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 30, 2010, 3:35 AM
 */

#ifndef CIRCULAR_ARRAY_QUEUE_H
#    define	CIRCULAR_ARRAY_QUEUE_H

#include <cstddef>

namespace cscience {
namespace queue {

// TODO: Use an object to encapsulate the array
template <typename TValue>
class circular_array_queue {
public:
	typedef TValue value_type;
	typedef size_t size_type;

private:
	value_type *m_queue;
	size_type m_offset;
	size_type m_size;
	size_type m_capacity;

public:
	circular_array_queue(size_type capacity):
		m_queue(0),
		m_offset(0),
		m_size(0),
		m_capacity(capacity)
	{
		m_queue = new value_type[m_capacity];
	}

	~circular_array_queue() {
		delete [] m_queue;
	}

	void enqueue(value_type const &value) {
		m_queue[(m_offset + m_size) % m_capacity] = value;

		++m_size;
	}

	void dequeue() {
		m_offset = (m_offset + 1) % m_capacity;

		--m_size;
	}

	value_type const &front() const {
		return m_queue[m_offset];
	}

	value_type &front() {
		return m_queue[m_offset];
	}

	void clear() {
		m_size = 0;
	}

	bool full() const {
		return m_size == m_capacity;
	}

	bool empty() const {
		return !m_size;
	}

	size_type size() const {
		return m_size;
	}

	value_type const &operator[](size_type i) const {
		return m_queue[(m_offset + i) % m_capacity];
	}
};

} // namespace cscience {
} // namespace queue {

#endif	/* CIRCULAR_ARRAY_QUEUE_H */
