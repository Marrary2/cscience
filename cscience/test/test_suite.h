/*
 * test_suite.h
 *
 *  Created on: Aug 5, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_test__test_suite_h
#define INCLUDED_cscience_test__test_suite_h

#include "./test_case.h"

#include <string>
#include <list>
#include <memory>

namespace cscience {
namespace test {

class test_suite {
	typedef std::list<std::unique_ptr<test_case>> test_list;

	test_list cases;

public:
	template <typename TTest>
	test_suite &add(std::string const &name, TTest test) {
		cases.push_back(
			std::unique_ptr<test_case>(
				new test_case_adapter<TTest>(name, test)
			)
		);

		return *this;
	}

	template <typename TException, typename TTest>
	test_suite &add(std::string const &name, TTest test) {
		typedef test_case_adapter<TTest> adapter_t;

		cases.push_back(
			std::unique_ptr<test_case>(
				new test_case_expecting_exception<TException, adapter_t>(
					adapter_t(name, test)
				)
			)
		);

		return *this;
	}

	test_suite &add(test_case *test) {
		if(!test) {
			throw std::invalid_argument("given test case can't be null");
		}

		cases.push_back(
			std::unique_ptr<test_case>(test)
		);

		return *this;
	}

	void clear() { cases.clear(); }

	bool empty() const { return cases.empty(); }

	typedef test_list::size_type size_type;
	size_type size() const { return cases.size(); }

	typedef test_list::const_iterator const_iterator;
	const_iterator begin() const { return cases.begin(); }
	const_iterator end() const { return cases.end(); }

	typedef test_list::iterator iterator;
	iterator begin() { return cases.begin(); }
	iterator end() { return cases.end(); }
};

} // namespace test {
} // namespace cscience {

#endif // INCLUDED_cscience_test__test_suite_h
