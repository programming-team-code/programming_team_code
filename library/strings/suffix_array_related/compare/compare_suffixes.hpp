/** @file */
#pragma once
#include "../suffix_array.hpp"
/**
 * @code{.cpp}
       string s;
       auto [sa, sa_inv] = get_sa(s, 256);
       suf_cmp(sa_inv, le1, le2);
       // or
       vector<int> a;
       auto [sa, sa_inv] = get_sa(a, 100'005);
       suf_cmp(sa_inv, le1, le2);
 * @endcode
 *
 * @param sa_inv inverse permutation of suffix array
 * @param le1,le2 defines suffixes [le1, n), [le2, n), note passing le1,le2 = n is okay
 * @returns a value `cmp` where:
 *     - cmp < 0 iff s.substr(le1) < s.substr(le2)
 *     - cmp = 0 iff s.substr(le1) = s.substr(le2)
 *     - cmp > 0 iff s.substr(le1) > s.substr(le2)
 * @time O(1)
 * @space O(1)
 */
inline int suf_cmp(const vector<int>& sa_inv, int le1, int le2) {
	assert(0 <= min(le1, le2) && max(le1, le2) <= ssize(sa_inv));
	return max(le1, le2) == ssize(sa_inv) ? le2 - le1 : sa_inv[le1] - sa_inv[le2];
}
