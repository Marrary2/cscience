/*
 * iterator_rolling_hasher.h
 *
 *  Created on: 11/04/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef ITERATOR_ROLLING_HASHER_H_
#	define ITERATOR_ROLLING_HASHER_H_

namespace cscience {
namespace hash {

template <typename rolling_hash, typename iterator>
class iterator_rolling_hasher
{
public:
	typedef typename rolling_hash::hash_type hash_type;
	typedef size_t size_type;

private:
	rolling_hash hasher;
	iterator m_begin;
	iterator i;
	iterator const m_end;

public:
	iterator_rolling_hasher(iterator begin, iterator const end, size_type size):
		m_begin(begin),
		m_end(end),
		i(begin + size)
	{
		assert(!(end < begin));
		assert(!(end - begin < size));

		hasher.hash(begin, i);
	}

	size_type size() const {
		return i - m_begin;
	}

	bool operator ++() {
		hasher.move(*i, *m_begin);

		++i;
		++m_begin;

		return *this;
	}

	bool operator ++(int) {
		if(!bool(*this)) {
			return false;
		}

		++*this;

		return true;
	}

	iterator const &begin() const {
		return m_begin;
	}

	iterator const &end() const {
		return i;
	}

	bool operator ==(hash_type const &hash) const {
		return hasher == hash;
	}

	bool operator !=(hash_type const &hash) const {
		return hasher != hash;
	}

	bool operator !() const {
		return !bool(*this);
	}

	explicit operator bool() const {
		return i < m_end;
	}

	explicit operator hash_type const &() const {
		return hasher;
	}
};

} // namespace hash {
} // namespace cscience {

#endif /* ITERATOR_ROLLING_HASHER_H_ */

