/** @file */
#pragma once
#include "../lcp_query.hpp"
/**
 * @param le1,ri1 first substring [le1, ri1)
 * @param le2,ri2 second substring [le2, ri2)
 * @returns a value `cmp` where:
 *     - cmp < 0 iff s.substr(le1, ri1 - le1) < s.substr(le2, ri2 - le2)
 *     - cmp = 0 iff s.substr(le1, ri1 - le1) = s.substr(le2, ri2 - le2)
 *     - cmp > 0 iff s.substr(le1, ri1 - le1) > s.substr(le2, ri2 - le2)
 * @time O(1)
 * @space O(1)
 */
inline int substr_cmp(int le1, int ri1, int le2, int ri2) {
	assert(0 <= le1 && le1 <= ri1 && ri1 <= n);
	assert(0 <= le2 && le2 <= ri2 && ri2 <= n);
	int len1 = ri1 - le1;
	int len2 = ri2 - le2;
	return len_lcp(le1, le2) >= min(len1, len2) ? len1 - len2 : sa_inv[le1] - sa_inv[le2];
}
