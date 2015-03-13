/* 
 * File:   maximum_submatrix.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 26, 2010, 11:52 PM
 */

#ifndef MAXIMUM_SUBMATRIX_H
#    define	MAXIMUM_SUBMATRIX_H

#include <algorithm/dynamic_programming/maximum_subarray.h>

#include <vector>
#include <utility>
#include <exception>
#include <cstdlib>

namespace cscience {
namespace algorithm {
namespace dynamic_programming {

// O(n^3)
template <typename TData>
TData kadane_2d(std::vector<std::vector<TData> > const &data, size_t n, size_t m, size_t &x1, size_t &x2, size_t &y1, size_t &y2)
{
	using namespace std;

	if(n < 1 || m < 1)
	{
		throw exception();
	}

	vector<vector<TData> > prefixSum(n);

	for(size_t i = 0; i < n; ++i)
	{
		prefixSum[i].resize(m);

		for(size_t j = 0; j < m; ++j)
		{
			prefixSum[i][j] = data[i][j];

			if(i)
			{
				prefixSum[i][j] += prefixSum[i - 1][j];
			}
		}
	}

	x1 = x2 = y1 = y2 = 0;
	TData sum = data[0][0];

	for(size_t i = 0; i < n; ++i)
	{
		for(size_t j = i; j < n; ++j)
		{
			vector<TData> block(m);

			for(size_t k = 0; k < m; ++k)
			{
				block[k] = prefixSum[j][k];

				if(i)
				{
					block[k] -= prefixSum[i - 1][k];
				}
			}

			size_t offset, end;
			TData local = kadane_1d(&block[0], block.size(), offset, end);

			if(local > sum)
			{
				y1 = i;
				x1 = offset;
				y2 = j;
				x2 = end;
				sum = local;
			}
		}
	}

	return sum;
}

#define maximum_submatrix_algorithm kadane_2d

} // namespace dynamic_programming {
} // namespace algorithm {
} // namespace cscience {

#endif	/* MAXIMUM_SUBMATRIX_H */
