/*
 * quick_sort.h
 *
 *  Created on: 27/11/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_sort__quick_sort_h
#define INCLUDED_cscience_sort__quick_sort_h

#include <iterator_traits>
#include <functional>

#include <cassert>

#include "./partition.h"

namespace cscience {
namespace sort {

// TODO: Turn this algorithm into a functional structure
// TODO: Use a custom pivot heuristic

template <typename iterator, size_t threshold = 1, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
void quick_sort(iterator begin, iterator end, TComparator comparator = TComparator()) {
	assert(!(end < begin));

	while(begin != end && threshold < end - begin) {
		auto pivot = partition(begin, end - 1, comparator);

		if(end - pivot < pivot - begin) {
			quick_sort(pivot + 1, end, comparator);
			end = pivot - 1;
		}
		else {
			quick_sort(begin, pivot, comparator);
			begin = pivot + 1;
		}
	}
}

} // namespace sort {
} // namespace cscience {

#endif // INCLUDED_cscience_sort__quick_sort_h
