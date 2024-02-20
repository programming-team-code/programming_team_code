/** @file */
#pragma once
#include "../bit.hpp"
/**
 * Requires bit.sum(i, i + 1) >= 0
 * @param bit binary indexed tree
 * @param sum see return
 * @returns min pos such that sum of range [0, pos) >= sum (or n+1)
 * @time O(log n)
 * @space O(1)
 */
template <class T> inline int lower_bound(BIT<T>& bit, T sum) {
	if (sum <= 0) return 0;
	int pos = 0;
	for (int pw = 1 << __lg(ssize(bit.s) | 1); pw; pw >>= 1)
		if (pos + pw <= ssize(bit.s) && bit.s[pos + pw - 1] < sum)
			pos += pw, sum -= bit.s[pos - 1];
	return pos + 1;
}
