/*
 * xor_rolling_hash.h
 *
 *  Created on: 08/04/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef XOR_ROLLING_HASH_H_
#	define XOR_ROLLING_HASH_H_

namespace cscience {
namespace hash {

template <typename value_type, typename hash_t = value_type>
struct xor_rolling_hasher {
	typedef hash_t hash_type;

private:
	hash_type m_hash;

public:
	xor_rolling_hasher():
		m_hash(0)
	{
	}

	template <typename iterator>
	xor_rolling_hasher(iterator begin, iterator end):
		m_hash(0)
	{
		hash(begin, end);
	}

	template <typename iterator>
	xor_rolling_hasher &hash(iterator begin, iterator end) {
		while(begin < end) {
			m_hash ^= *begin;
			++begin;
		}

		return *this;
	}

	xor_rolling_hasher &move(value_type const &out, value_type const &in) {
		m_hash ^= out ^ in;
		return *this;
	}

	xor_rolling_hasher &operator >>(value_type const &out) {
		m_hash ^= out;
		return *this;
	}

	xor_rolling_hasher &operator <<(value_type const &in) {
		m_hash ^= in;
		return *this;
	}

	bool operator ==(hash_type const &hash) const {
		return m_hash == hash;
	}

	bool operator !=(hash_type const &hash) const {
		return m_hash != hash;
	}

	explicit operator hash_type const &() const {
		return m_hash;
	}
};

} // namespace hash {
} // namespace cscience {

#endif /* XOR_ROLLING_HASH_H_ */
