/*
 * selection_sort.h
 *
 *  Created on: 27/11/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_sort__selection_sort_h
#define INCLUDED_cscience_sort__selection_sort_h

#include <iterator_traits>
#include <functional>

#include <cassert>

namespace cscience {
namespace sort {

// TODO: Turn this algorithm into a functional structure

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
void selection_sort(iterator begin, iterator end, TComparator comparator = TComparator()) {
	assert(!(end < begin));

	for(; begin != end; ++begin) {
		auto min = *begin;

		for(auto i = begin + 1; i != end; ++i) {
			if(comparator(*i, *min)) {
				min = i;
			}
		}

		swap(*begin, *min);
	}
}

} // namespace sort {
} // namespace cscience {

#endif // INCLUDED_cscience_sort__selection_sort_h
