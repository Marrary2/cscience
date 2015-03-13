/*
 * binary_search.h
 *
 *  Created on: 27/11/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_search__binary_search_h
#define INCLUDED_cscience_search__binary_search_h

#include <iterator_traits>

#include <cassert>

namespace cscience {
namespace search {

template <typename iterator>
iterator binary_search(iterator  begin, iterator end, std::iterator_traits<iterator> const &value) {
	assert(!(end < begin));

	while(begin != end) {
		auto pivot = begin + ((end - begin) / 2);

		if(*pivot < value) {
			begin = pivot + 1;
		}
		else if(value < *pivot) {
			end = pivot;
		}
		else {
			return pivot;
		}
	}

	return end;
}

} // namespace search {
} // namespace cscience {

#endif // INCLUDED_cscience_search__binary_search_h
