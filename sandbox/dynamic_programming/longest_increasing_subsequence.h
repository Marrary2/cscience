/*
 * longest_increasing_subsequence.h
 *
 *  Created on: Dec 23, 2010
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef LONGEST_INCREASING_SUBSEQUENCE_H_
#	define LONGEST_INCREASING_SUBSEQUENCE_H_

#include <vector>
#include <stack>
#include <iostream>
#include <cstdlib>

namespace cscience {
namespace algorithm {
namespace dynamic_programming {

template <typename TData>
void print_longest_increasing_subsequence(TData const *data, size_t tail, size_t length, size_t const *predecessor)
{
	using namespace std;

	stack<size_t> lisIndexes;

	for(size_t i = tail; length--; i = predecessor[i])
	{
		lisIndexes.push(i);
	}

	cout << "LIS:";

	while(!lisIndexes.empty())
	{
		cout << ' ' << data[lisIndexes.top()];

		lisIndexes.pop();
	}

	cout << endl;
}

template <typename TData>
void quadratic_longest_increasing_subsequence(TData const *data, size_t n)
{
	using namespace std;

	if(!data || n < 1)
	{
		return;
	}

	vector<size_t> sizeAt(n);
	vector<size_t> predecessor(n);

	size_t lisTail = 0;

	for(size_t i = 0; i < n; ++i)
	{
		sizeAt[i] = 0;
		predecessor[i] = i;

		for(size_t j = i; j--; )
		{
			if(data[j] < data[i] && sizeAt[j] > sizeAt[i])
			{
				sizeAt[i] = sizeAt[j];
				predecessor[i] = j;
			}
		}

		++sizeAt[i];

		if(sizeAt[i] > sizeAt[lisTail])
		{
			lisTail = i;
		}
	}

	print_longest_increasing_subsequence(data, lisTail, sizeAt[lisTail], &predecessor[0]);
}

template <typename TData>
void nlgn_longest_increasing_subsequence(TData const *data, size_t n)
{
	using namespace std;

	if(!data || n < 1)
	{
		return;
	}

	vector<size_t> predecessor(n); // index of the predecessor of element with index i, where i is the index of both this vector and input
	vector<size_t> lisTop(n); // index of smallest element ending lis of size i, where i is the index of this vector

	predecessor[0] = 0;
	//size_t tail = 0;
	size_t largest = 1;

	for(size_t i = 1; i < n; ++i)
	{
		// If current element ends current largest LIS, update largest LIS
		if(data[lisTop[largest - 1]] < data[i])
		{
			predecessor[i] = lisTop[largest - 1];
			lisTop[largest] = i;
			++largest;
		}
		else
		{
			size_t length = 0;

			for(size_t right = largest - 1; length < right; )
			{
				size_t center = length + ((right - length) / 2);

				if(data[lisTop[center]] < data[i])
				{
					length = center + 1;
				}
				else
				{
					right = center;
				}
			}

			if(data[i] < data[lisTop[length]])
			{
				if(length > 0)
				{
					predecessor[i] = lisTop[length - 1];
				}

				lisTop[length] = i;
			}
		}
	}

	print_longest_increasing_subsequence(data, lisTop[largest - 1], largest, &predecessor[0]);
}

#define longest_increasing_subsequence_algorithm nlgn_longest_increasing_subsequence

} // namespace dynamic_programming {
} // namespace algorithm {
} // namespace cscience {

#endif /* LONGEST_INCREASING_SUBSEQUENCE_H_ */
