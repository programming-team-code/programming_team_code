/** @file */
#pragma once
#include "../bit.hpp"
/**
 * range update, point query
 */
template <class T> struct bit_rupq {
	int n;
	BIT<T> bit;
	/**
	 * @param a_n size
	 * @time O(n)
	 * @space O(n)
	 */
	bit_rupq(int a_n) : n(a_n), bit(n) {}
	/**
	 * @param a initial array
	 * @time O(n)
	 * @space O(n)
	 */
	bit_rupq(vector<T> a) : n(ssize(a)) {
		adjacent_difference(begin(a), end(a), begin(a));
		bit = {a};
	}
	/**
	 * does a[le] += d, a[le + 1] += d, .., a[ri - 1] += d
	 *
	 * @param le,ri defines range [le, ri)
	 * @param d delta to add to all indexes in range
	 * @time O(log n)
	 * @space O(1)
	 */
	inline void update(int le, int ri, T d) {
		assert(0 <= le && le <= ri && ri <= n);
		if (le < n) bit.update(le, d);
		if (ri < n) bit.update(ri, -d);
	}
	/**
	 * @param i index
	 * @returns a[i]
	 * @time O(log n)
	 * @space O(1)
	 */
	inline T get_index(int i) {
		assert(0 <= i && i < n);
		return bit.sum(i + 1);
	}
};
