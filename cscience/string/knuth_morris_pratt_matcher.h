/*
 * knuth_morris_pratt_matcher.h
 *
 *  Created on: 08/04/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef KMP_MATCHER_H_
#	define KMP_MATCHER_H_

#include <vector>

#include <cassert>

namespace cscience {
namespace string {

template <typename needle_iterator>
class knuth_morris_pratt_matcher {
	vector<needle_iterator> table;
	size_t q;

public:
	knuth_morris_pratt_matcher(needle_iterator const begin, needle_iterator const end):
		table(end - begin),
		q(0)
	{
		assert(!(end < begin));

		auto q = table[0] = begin;

		for(auto i = begin + 1; i < end; ++i) {
			while(q > begin && *q != *i) {
				q = table[q - 1 - begin];
			}

			if(*q == *i) {
				++q;
			}

			table[i - begin] = q;
		}
	}

	template <typename haystack_iterator>
	haystack_iterator seek(haystack_iterator begin, haystack_iterator end) {
		assert(!(end < begin));

		for(auto i = begin; i < end; ++i) {
			while(q > 0 && table[q] != *i) {
				--q;
			}

			if(table[q] == *i) {
				++q;
			}

			if(q == table.size()) {
				return i + 1;
			}
		}

		return end;
	}

	void clear() {
		q = 0;
	}

	explicit operator bool() const {
		return q == table.size();
	}
};

} // namespace string {
} // namespace cscience {

#endif /* KMP_MATCHER_H_ */
