/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
       vector<int64_t> a;
       auto ri = mono_st(a, less()), le = mono_range(ri); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param ri monotonic stack array of a
 * @returns (if you use less()) vector le such that:
 *     - le[i] < i < ri[i]
 *     - a[i] is the min of exclusive-exclusive range (le[i], ri[i])
 *     - le[i] is the max index such that a[le[i]] < a[i], or -1
 *     - ri[i] is the min index such that a[i] >= a[ri[i]], or n
 * @time O(n)
 * @space two O(n) vectors are allocated and returned
 */
vector<int> mono_range(const vector<int>& ri) {
	vector le(ssize(ri), -1);
	for (int i = 0; i < ssize(ri); i++)
		for (int j = i + 1; j != ri[i]; j = ri[j]) le[j] = i;
	return le;
}
