/*
 * longest_common_subsequence.h
 *
 *  Created on: Dec 23, 2010
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef LONGEST_COMMON_SUBSEQUENCE_H_
#	define LONGEST_COMMON_SUBSEQUENCE_H_

#include <vector>
#include <iomanip>
#include <cstddef>

namespace cscience {
namespace algorithm {
namespace dynamic_programming {

template <typename TData>
void longest_common_subsequence(TData const *a, size_t n, TData const *b, size_t m)
{
	using namespace std;

	vector<vector<size_t> > output(n + 1);

	for(size_t i = 0; i <= n; ++i)
	{
		output[i].resize(m + 1);

		if(i)
		{
			output[i][0] = 0;
		}
		else
		{
			for(size_t j = 0; j <= m; ++j)
			{
				output[i][j] = 0;
			}
		}
	}

	for(size_t i = 1; i <= n; ++i)
	{
		for(size_t j = 1; j <= m; ++j)
		{
			output[i][j] = max(output[i - 1][j - 1], max(output[i - 1][j], output[i][j - 1]))
				+ (a[i - 1] == b[j - 1] ? 1 : 0);
		}
	}

	for(size_t i = 0; i <= n; ++i)
	{
		for(size_t j = 0; j <= m; ++j)
		{
			cout << setw(3) << output[i][j] << setw(0) << ' ';
		}

		cout << endl;
	}
}

} // namespace dynamic_programming {
} // namespace algorithm {
} // namespace cscience {

#endif /* LONGEST_COMMON_SUBSEQUENCE_H_ */
