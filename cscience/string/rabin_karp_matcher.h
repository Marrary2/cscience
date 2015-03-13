/*
 * rabin_karp_matcher.h
 *
 *  Created on: 08/04/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef RABIN_KARP_MATCHER_H_
#	define RABIN_KARP_MATCHER_H_

namespace cscience {
namespace string {

template <typename rolling_hash, typename needle_iterator>
class rabin_karp_matcher
{
	typename rolling_hash::hash_type hash;
	needle_iterator const nbegin;
	needle_iterator const nend;

public:
	rabin_karp_matcher(needle_iterator const begin, needle_iterator const end):
		nbegin(begin),
		nend(end)
	{
		assert(!(end < begin));

		hash = rolling_hash().hash(begin, end);
	}

	template <typename haystack_iterator>
	haystack_iterator find(haystack_iterator begin, haystack_iterator end) {
		assert(!(end < begin));

		if(end - begin < nend - nbegin) {
			return end;
		}

		auto i = begin + (nend - nbegin);
		rolling_hash window;

		window.hash(begin, i);

		do {
			if(window == hash) {
				auto needle = nbegin;

				for(auto j = begin; needle != nend && *j == *needle; ++j, ++needle);

				if(needle == nend) {
					return begin;
				}
			}

			window.move(*begin, *i);
			++begin;
		} while(i++ < end);

		return end;
	}
};

} // namespace string {
} // namespace cscience {

#endif /* RABIN_KARP_MATCHER_H_ */
