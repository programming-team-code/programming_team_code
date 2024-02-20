/** @file */
#pragma once
#include "../../data_structures/rmq.hpp"
#include "suffix_array.hpp"
#include "lcp_array.hpp"
/**
 * query for longest common prefix of 2 suffixes
 *
 * note if one of the suffixes is the entire string (i1 == 0 || i2 == 0)
 * then it's the same as z algorithm
 */
template <class T> struct lcp_query {
	vector<int> sa, sa_inv, lcp;
	RMQ<int, function<int(int, int)>> rmq;
	/**
	 * @param s,max_val string/array with 0 <= s[i] < max_val
	 * @time O((n log n) + max_val)
	 * @space O(n log n) for RMQ's; a O(max_val) vector `freq` is used temporarily during get_sa
	 */
	lcp_query(const T& s, int max_val) {
		auto ret = get_sa(s, max_val);
		sa = ret[0], sa_inv = ret[1];
		lcp = get_lcp_array(sa, sa_inv, s);
		rmq = {lcp, [](int x, int y) {return min(x, y);}};
	}
	/**
	 * @param i1,i2 defines substrings [i1, n), [i2, n), note passing i1,i2 = n is okay
	 * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
	 * @time O(1)
	 * @space O(1)
	 */
	inline int get_lcp(int i1, int i2) {
		int n = ssize(sa);
		if (i1 > i2) swap(i1, i2);
		assert(0 <= i1 && i2 <= n);
		if (i1 == i2 || i2 == n) return n - i2;
		auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
		return rmq.query(le, ri);
	}
};
