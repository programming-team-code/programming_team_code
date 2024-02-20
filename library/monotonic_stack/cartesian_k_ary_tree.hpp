/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 *   when cmp is less_equal():
 *   a = {2, 1, 3, 1, 1, 0, 2, 2, 1, 0, 2}
 *       (---------------x---------------)
 *       (---x---------) | (------x)   (x)
 *       (x) | (x)       | (x---) |     |
 *        |  |  |        |  |     |     |
 * index: 0  1  2  3  4  5  6  7  8  9  10
 *
 * nodes are the left-most min of their subarray:
 * p[0] = p[2] = 1
 * p[6] = 8
 * p[1] = p[8] = p[10] = 5
 * p[5] = 11 = n (root)
 *
 * indexes 3, 4, 7, 9 are not nodes; here p maps i to left-most min in their subarray:
 * p[3] = p[4] = 1
 * p[7] = 6
 * p[9] = 5
 *
 * @code{.cpp}
       auto ri = mono_st(a, less_equal()), p = cart_k_ary_tree(a, ri); // min cart tree
       auto ri = mono_st(a, greater_equal()), p = cart_k_ary_tree(a, ri); // max cart tree
       bool is_node = (p[i] > i || a[i] != a[p[i]]);
 * @endcode
 *
 * @param a,ri array and its monotonic stack
 * @returns parent array
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T> vector<int> cart_k_ary_tree(const vector<T>& a, const vector<int>& ri) {
	vector<int> p(ri);
	for (int i = 0; i < ssize(a); i++)
		for (int j = i + 1; j != ri[i]; j = ri[j])
			if (ri[j] == ri[i] || a[i] == a[ri[j]])
				p[j] = (p[i] > i || a[i] != a[p[i]] ? i : p[i]);
	return p;
}
