/*
 * rolling_hasher.h
 *
 *  Created on: 08/04/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef ROLLING_HASHER_H_
#	define ROLLING_HASHER_H_

#include "../queue/circular_array_queue.h"

namespace cscience {
namespace hash {

template <typename THasher>
class rolling_hasher
{
public:
	typedef THasher hasher_type;
	typedef typename hasher_type::hash_type hash_type;
	typedef typename hasher_type::value_type value_type;
	typedef size_t size_type;

private:
	hasher_type m_hasher;
	cscience::queue::circular_array_queue<value_type> m_queue;

public:
	rolling_hasher(size_type size):
		m_queue(size)
	{
	}

	size_type size() const {
		return m_queue.size();
	}

	value_type const &operator[](size_type i) const {
		return m_queue[i];
	}

	rolling_hasher &operator <<(value_type const &in) {
		if(m_hasher.size() < m_queue.size()) {
			m_hasher << in;
		}
		else {
			m_hasher.move(in, m_queue.dequeue());
		}

		m_queue.enqueue(in);

		return *this;
	}

	bool operator ==(hash_type const &hash) const {
		return m_hasher == hash;
	}

	bool operator !=(hash_type const &hash) const {
		return m_hasher != hash;
	}

	bool operator !() const {
		return m_hasher.size() != m_queue.size();
	}

	explicit operator bool() const {
		return m_hasher.size() == m_queue.size();
	}

	explicit operator hash_type const &() const {
		return m_hasher;
	}
};

} // namespace hash {
} // namespace cscience {

#endif /* ROLLING_HASHER_H_ */
