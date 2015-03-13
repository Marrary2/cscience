/*
 * test_case.h
 *
 *  Created on: Aug 5, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_test__test_case_h
#define INCLUDED_cscience_test__test_case_h

#include "./test_exception.h"

#include <string>
#include <typeinfo>

namespace cscience {
namespace test {

class test_case {
	std::string m_name;

public:
	test_case(std::string const &name = std::string()):
		m_name(name)
	{
	}

	test_case(test_case const &other):
		m_name(other.name())
	{
	}

	virtual ~test_case() {
	}

	virtual void run() = 0;

	virtual std::string const &name() const {
		return this->m_name;
	}
};

template <typename TException, typename TTestCase>
class test_case_expecting_exception:
	public test_case
{
	TTestCase m_inner;

public:
	test_case_expecting_exception(TTestCase inner):
		m_inner(inner)
	{
	}

	test_case_expecting_exception(test_case_expecting_exception const &other):
		m_inner(other.m_inner)
	{
	}

	void run() {
		try {
			this->m_inner.run();

			throw exception_expected_error(
				typeid(TException).name()
			);
		}
		catch(TException const &e) {
			// This exception is expected
		}
	}

	std::string const &name() const {
		return this->m_inner.name();
	}
};

template <typename TTest>
class test_case_adapter:
	public test_case
{
	TTest m_test;

public:
	test_case_adapter(std::string const &name, TTest test):
		test_case(name),
		m_test(test)
	{
	}

	test_case_adapter(test_case_adapter const &other):
		test_case(other.name()),
		m_test(other.m_test)
	{
	}

	void run() {
		this->m_test();
	}
};

} // namespace test {
} // namespace cscience {

#endif // INCLUDED_cscience_test__test_case_h
