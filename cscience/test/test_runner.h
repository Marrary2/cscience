/*
 * test_runner.h
 *
 *  Created on: Aug 5, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_test__test_runner_h
#define INCLUDED_cscience_test__test_runner_h

#include "./test_listener.h"

#include <exception>

#include <cassert>

namespace cscience {
namespace test {

template <typename TListener = nop_test_listener>
class test_runner {
	TListener listener;

public:
	test_runner(TListener listener = TListener()):
		listener(listener)
	{
	}

	template <typename TTestSet>
	void run(TTestSet const &tests) {
		run(tests.begin(), tests.end());
	}

	template <typename iterator>
	void run(iterator begin, iterator end) {
		assert(!(end < begin));

		listener.start();

		unsigned succeeded = 0;
		unsigned failed = 0;
		unsigned total = 0;

		for(; begin != end; ++begin, ++total) {
			auto name = (*begin)->name();

			try {
				listener.running(name);
				(*begin)->run();

				listener.succeeded(name);
				++succeeded;
			}
			catch(std::exception &e) {
				listener.failed(name, e);
				++failed;
			}
			catch(...) {
				listener.failed(name);
			}
		}

		listener.outcome(succeeded, failed, total - succeeded - failed, total);
	}
};

} // namespace test {
} // namespace cscience {

#endif // INCLUDED_cscience_test__test_runner_h
