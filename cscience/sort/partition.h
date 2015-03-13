/*
 * partition.h
 *
 *  Created on: 27/11/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_sort__partition_h
#define INCLUDED_cscience_sort__partition_h

#include <iterator_traits>
#include <functional>

#include <cstdlib>
#include <cassert>

namespace cscience {
namespace sort {

// TODO: Turn these functions into functional structures

namespace internal {

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
iterator median_of_three(iterator left, iterator median, iterator right, TComparator &comparator) {
	assert(!(right < median));
	assert(!(median < left));

	if(comparator(*right, *median)) swap(*median, *right);
	if(comparator(*median, *left)) swap(*left, *median);
	if(comparator(*median, *right)) swap(*right, *median);

	return right;
}

} // namespace internal {

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
iterator rightmost_pivot(iterator left, iterator right, TComparator &comparator) {
	assert(!(right < left));

	return right;
}

template <typename iterator>
iterator leftmost_pivot(iterator left, iterator right, TComparator &comparator) {
	assert(!(right < left));

	return left;
}

// TODO: Use a custom random function
template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
iterator random_pivot(iterator left, iterator right, TComparator &comparator) {
	assert(!(right < left));

	return left + (rand() % (right - left + 1));
}

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
iterator median_of_three(iterator left, iterator right, TComparator &comparator) {
	assert(!(right < left));

	return internal::median_of_three(
		left,
		left + ((right - left) / 2),
		right,
		comparator
	);
}

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
iterator median_of_random_three(iterator left, iterator right, TComparator &comparator) {
	assert(!(right < left));

	auto median = random_pivot(left, right);

	return internal::median_of_three(
		random_pivot(left, median),
		median,
		random_pivot(median, right),
		comparator
	);
}

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
iterator randomized_median_of_three(iterator left, iterator right, TComparator &comparator) {
	assert(!(right < left));

	return internal::median_of_three(
		left,
		random_pivot(left, right),
		right,
		comparator
	);
}

// TODO: Use a custom pivot heuristic

template <typename iterator, typename TComparator = std::less<typename iterator_traits<iterator>::value_type>>
iterator partition(iterator left, iterator right, TComparator &comparator) {
	assert(!(right < left));

	if(left == right) return right;

	auto pivot = median_of_three(left, right--, comparator);

	for(;;) {
		while(comparator(*left, *pivot)) ++left;

		while(!comparator(*right, *pivot)) {
			if(left == right) break;

			--right;
		}

		swap(*left, *right);
	}

	swap(*pivot, *left);

	return left;
}

} // namespace sort {
} // namespace cscience {

#endif // INCLUDED_cscience_sort__partition_h
