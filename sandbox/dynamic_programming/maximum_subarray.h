/* 
 * File:   maximum_subarray.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 26, 2010, 11:13 PM
 */

#ifndef MAXIMUM_SUBARRAY_H
#    define	MAXIMUM_SUBARRAY_H

#include <utility>
#include <exception>
#include <cstdlib>

namespace cscience {
namespace algorithm {
namespace dynamic_programming {

// O(n)
template <typename TData>
TData kadane_1d(TData const *data, size_t n, size_t &start, size_t &end)
{
	using namespace std;

	if(!data || n < 1)
	{
		throw exception();
	}

	start = end = 0;
	TData sum = data[0];
	TData current = 0;

	for(size_t i = 0, offset = 0; i < n; ++i)
	{
		current += data[i];

		if(current > sum)
		{
			start = offset;
			end = i;
			sum = current;
		}

		if(current < 0)
		{
			current = 0;
			offset = i + 1;
		}
	}

	return sum;
}

#define maximum_subarray_algorithm kadane_1d

} // namespace dynamic_programming {
} // namespace algorithm {
} // namespace cscience {

#endif	/* MAXIMUM_SUBARRAY_H */
