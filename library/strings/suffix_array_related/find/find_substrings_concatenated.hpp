/** @file */
#pragma once
#include "../lcp_query.hpp"
#include "match.hpp"
/**
 * @param lq lcp query struct
 * @param substrs this defines query string t as:
 *     s.substr(substrs[0][0], substrs[0][1] - substrs[0][0]) +
 *     s.substr(substrs[1][0], substrs[1][1] - substrs[1][0]) +
 *     ...
 *     s.substr(substrs.back()[0], substrs.back()[1] - substrs.back()[0])
 * @returns see match
 * @time O(ssize(substrs) * log(|s|))
 * @space O(1)
 */
template <class T> inline match find_substrs_concated(lcp_query<T>& lq,
        const vector<array<int, 2>>& substrs) {
	using dt = array<int, 3>;
	int n = ssize(lq.sa), sa_le = 0, sa_ri = n, str_le = 0, str_ri = 0, sum_len = 0;
	auto cmp = [&](int i, const dt & x) -> bool {
		int j = i + sum_len, lcp = min(lq.get_lcp(j, x[0]), x[1]);
		if (lcp + sum_len > str_ri - str_le) str_le = i, str_ri = j + lcp;
		if (lcp < min(n - j, x[1])) return lq.sa_inv[j] - lq.sa_inv[x[0]] < x[2];
		return x[2] ^ (n - j < x[1]);
	};
	for (auto [le, ri] : substrs) {
		assert(0 <= le && le <= ri && ri <= n);
		sa_le = lower_bound(begin(lq.sa) + sa_le, begin(lq.sa) + sa_ri, dt{le, ri - le, 0}, cmp) - begin(lq.sa);
		sa_ri = lower_bound(begin(lq.sa) + sa_le, begin(lq.sa) + sa_ri, dt{le, ri - le, 1}, cmp) - begin(lq.sa);
		sum_len += ri - le;
	}
	return {sa_le, sa_ri, str_le, str_ri};
}
