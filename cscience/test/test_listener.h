/*
 * test_listener.h
 *
 *  Created on: 04/12/2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef INCLUDED_cscience_test__test_listener_h
#define INCLUDED_cscience_test__test_listener_h

namespace cscience {
namespace test {

struct nop_test_listener {
	void start() {
	}

	template <typename string_type>
	void running(string_type const &name) {
	}

	template <typename string_type>
	void succeeded(string_type const &name) {
	}

	template <typename string_type, typename exception_type>
	void failed(string_type const &name, exception_type const &e) {
	}

	template <typename string_type>
	void failed(string_type const &name) {
	}

	template <typename counter_type>
	void outcome(
		counter_type const &succeeded,
		counter_type const &failed,
		counter_type const &unknown,
		counter_type const &total
	) {
	}
};

} // namespace test {
} // namespace cscience {

#endif // INCLUDED_cscience_test__test_listener_h
