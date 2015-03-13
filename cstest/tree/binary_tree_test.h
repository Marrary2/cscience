/*
 * binary_tree_test.h
 *
 *  Created on: Sep 2, 2011
 *      Author: Marcelo Juchem <juchem at gmail dot com>
 */

#ifndef BINARY_TREE_TEST_H_
#define BINARY_TREE_TEST_H_

#include "../../cscience/tree/binary_tree.h"

#include <functional>

namespace cscience {
namespace tree {

void test() {
	typedef int value_type;
	typedef linked_binary_tree<value_type> tree_type;

	tree_type tree(4);
	auto left = tree.insert_left(2);
	left->insert_left(1);
	left->insert_right(3);
	auto right = tree.insert_right(6);
	right->insert_left(5);
	right->insert_right(7);

	for(auto i = tree.walker(); i && i.walk_left(); i.walk_right());
	for(auto i = tree.in_begin(); i != tree.in_end(); ++i);
	for(auto i = tree.pre_begin(); i != tree.pre_end(); ++i);
	for(auto i = tree.post_begin(); i != tree.post_end(); ++i);
	for(auto i = tree.level_begin(); i != tree.level_end(); ++i);
}

}
}

#endif /* BINARY_TREE_TEST_H_ */
