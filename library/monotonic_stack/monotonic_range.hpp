/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
       vector<int64_t> a;
       auto le = mono_st(a, less()), ri = mono_range(le); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param le monotonic stack array of a
 * @returns vector ri where ri[i] = min index such that: i < ri[i] and
 *          !cmp(a[i], a[ri[i]]). If no index exists, ri[i] = n
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> mono_range(const vector<int>& le) {
	vector<int> ri(ssize(le), ssize(le));
	for (int i = 0; i < ssize(le); i++)
		for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
	return ri;
}
