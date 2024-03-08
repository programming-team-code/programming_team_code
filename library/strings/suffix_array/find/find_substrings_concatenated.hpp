/** @file */
#pragma once
#include "../lcp_query.hpp"
#include "match.hpp"
/**
 * @param substrs this defines query string t as:
 *     s.substr(substrs[0][0], substrs[0][1] - substrs[0][0]) +
 *     s.substr(substrs[1][0], substrs[1][1] - substrs[1][0]) +
 *     ...
 *     s.substr(substrs.back()[0], substrs.back()[1] - substrs.back()[0])
 * @returns see match
 * @time O(ssize(substrs) * log(|s|))
 * @space O(1) space used during query, but with O(nlogn) precomp
 */
inline match find_substrs_concated(const vector<array<int, 2>>& substrs) {
	using dt = array<int, 3>;
	int sa_le = 0, sa_ri = n, str_le = 0, str_ri = 0, sum_len = 0;
	auto cmp = [&](int i, const dt & x) -> bool {
		int j = i + sum_len, lcp_len = min(len_lcp(j, x[0]), x[1]);
		if (lcp_len + sum_len > str_ri - str_le) str_le = i, str_ri = j + lcp_len;
		if (lcp_len < min(n - j, x[1])) return sa_inv[j] - sa_inv[x[0]] < x[2];
		return x[2] ^ (n - j < x[1]);
	};
	for (auto [le, ri] : substrs) {
		assert(0 <= le && le <= ri && ri <= n);
		sa_le = lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 0}, cmp) - begin(sa);
		sa_ri = lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 1}, cmp) - begin(sa);
		sum_len += ri - le;
	}
	return {sa_le, sa_ri, str_le, str_ri};
}
