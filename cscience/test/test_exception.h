/*
 * test_exception.h
 *
 *  Created on: Aug 5, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_test__test_exception_h
#define INCLUDED_cscience_test__test_exception_h

#include <stdexcept>
#include <sstream>

namespace cscience {
namespace test {

class exception_expected_error:
	public std::runtime_error
{
public:
	explicit exception_expected_error(std::string const &what):
		std::runtime_error(what)
	{
	}
};

template <typename TValue>
class unexpected_value_error:
	public std::runtime_error
{
public:
	explicit unexpected_value_error(TValue const &expected, TValue const &actual):
		std::runtime_error(
			[&](){
				std::ostringstream s;
				s << "expected = " << expected << ", actual = " << actual;
				return s.str();
			}()
		)
	{
	}
};

} // namespace test {
} // namespace cscience {

#endif // INCLUDED_cscience_test__test_exception_h
