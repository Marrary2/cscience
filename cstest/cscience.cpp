/*
 * File:   main.cpp
 * Author: juchem
 *
 * Created on December 9, 2010, 12:47 AM
 */

#include "../cscience/test/test.h"

#include "tree/cs_all_tests.h"

using namespace cscience::test;

int main(int argc, char** argv)
{
	test_suite suite;

	cscience::tree::test();

	suite.add(0);

	suite.run();

	return 0;
}
