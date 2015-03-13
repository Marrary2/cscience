/*
 * File:   edit_distance.h
 * Author: Marcelo Juchem <juchem at gmail dot com>
 *
 * Created on December 13, 2010, 9:14 PM
 */

#ifndef EDIT_DISTANCE_H
#    define	EDIT_DISTANCE_H

#include <vector>
#include <cstddef>

namespace cscience {
namespace algorithm {
namespace dynamic_programming {

template <typename cost_type = size_t>
struct edit_data
{
	enum edit_type
	{
		Match,
		Insert,
		Delete
	};

	edit_type type;
	cost_type cost;
};

template <typename TData>
void edit_distance(TData const *from, size_t const fromSize, TData const *to, size_t const toSize)
{
	using namespace std;

	if(!from || !to)
	{
		return;
	}

	typedef size_t cost_type;

	cost_type const insertCost = 1;
	cost_type const deleteCost = 1;
	cost_type const replaceCost = 1;
	cost_type const matchCost = 0;

	typedef edit_data<cost_type> data_t;

	vector<vector<data_t> > output(fromSize + 1);

	for(size_t i = 0; i <= fromSize; ++i)
	{
		output[i].resize(toSize + 1);

		if(i)
		{
			// Initialize first column with zero
			output[i][0].type = data_t::Delete;
			output[i][0].cost = output[i - 1][0].cost + deleteCost;
		}
		else
		{
			// Initialize first line with zero
			for(size_t j = 0; j <= toSize; ++j)
			{
				if(j)
				{
					output[i][j].type = data_t::Insert;
					output[i][j].cost = output[i][j - 1].cost + insertCost;
				}
				else
				{
					output[i][j].type = data_t::Match;
					output[i][j].cost = matchCost;
				}
			}
		}
	}

	for(size_t i = 1; i <= fromSize; ++i)
	{
		for(size_t j = 1; j <= toSize; ++j)
		{
			output[i][j].type = data_t::Match;
			output[i][j].cost = output[i - 1][j - 1].cost
				+ (from[i - 1] == to[j - 1] ? matchCost : replaceCost);

			cost_type localInsertCost = output[i][j - 1].cost + insertCost;

			if(localInsertCost < output[i][j].cost)
			{
				output[i][j].type = data_t::Insert;
				output[i][j].cost = localInsertCost;
			}

			cost_type localDeleteCost = output[i - 1][j].cost + deleteCost;

			if(localDeleteCost < output[i][j].cost)
			{
				output[i][j].type = data_t::Delete;
				output[i][j].cost = localDeleteCost;
			}
		}
	}

	for(size_t i = 0; i <= fromSize; ++i)
	{
		for(size_t j = 0; j <= toSize; ++j)
		{
			switch(output[i][j].type)
			{
				case data_t::Match:
					if(i && j && output[i][j].cost > output[i - 1][j - 1].cost)
					{
						cout << 'R';
					}
					else
					{
						cout << 'M';
					}
					break;
				case data_t::Insert:
					cout << 'I';
					break;
				case data_t::Delete:
					cout << 'D';
					break;
			}
		}

		cout << endl;
	}
}

} // namespace dynamic_programming {
} // namespace algorithm {
} // namespace cscience {

#endif	/* EDIT_DISTANCE_H */
