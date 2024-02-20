/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 *   when cmp is less():
 *   a = {2, 1, 3, 1, 1, 0, 2, 2, 1, 0, 2}
 *       (---------------------------x---)
 *       (---------------x---------)   (x)
 *       (------------x) | (------x)    |
 *       (---------x)    | (---x) |     |
 *       (---x---)       | (x) |  |     |
 *       (x) | (x)       |  |  |  |     |
 *        |  |  |        |  |  |  |     |
 * index: 0  1  2  3  4  5  6  7  8  9  10
 *
 * @code{.cpp}
       auto ri = mono_st(a, less()), p = cart_binary_tree(ri); // right-most min is root
       auto ri = mono_st(a, less_equal()), p = cart_binary_tree(ri); // left-most min is root
       auto ri = mono_st(a, greater()), p = cart_binary_tree(ri); // right-most max is root
       auto ri = mono_st(a, greater_equal()), p = cart_binary_tree(ri); // left-most max is root
 * @endcode
 * @param ri monotonic stack of array `a`
 * @returns parent array
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> cart_binary_tree(const vector<int>& ri) {
	vector<int> p(ri);
	for (int i = 0; i < ssize(p); i++)
		for (int j = i + 1; j != ri[i]; j = ri[j])
			if (ri[j] == ri[i]) p[j] = i;
	return p;
}
