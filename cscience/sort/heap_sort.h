/*
 * heap_sort.h
 *
 *  Created on: 27/11/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_sort__heap_sort_h
#define INCLUDED_cscience_sort__heap_sort_h

#include <iterator_traits>
#include <functional>

#include <cassert>

namespace cscience {
namespace sort {

// TODO: Turn this algorithm into a functional structure

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
void heap_sort(iterator begin, iterator end, TComparator comparator = TComparator()) {
	assert(!(end < begin));
}

} // namespace sort {
} // namespace cscience {

#endif // INCLUDED_cscience_sort__heap_sort_h
