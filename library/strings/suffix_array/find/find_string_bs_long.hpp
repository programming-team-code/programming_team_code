/** @file */
#pragma once
#include "match.hpp"
/**
 * @param t query string
 * @returns see match
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
inline match find_str_long(const T& t) {
	int s_le = 0, s_ri = 0;
	auto cmp = [&](int i, int cmp_val) -> bool {
		auto [it_s, it_t] = mismatch(begin(s) + i, end(s), begin(t), end(t));
		if (it_s - begin(s) - i > s_ri - s_le) s_le = i, s_ri = it_s - begin(s);
		if (it_s != end(s) && it_t != end(t)) return (*it_s) - (*it_t) < cmp_val;
		return cmp_val ^ (ssize(s) - i < ssize(t));
	};
	int sa_le = lower_bound(begin(sa), end(sa), 0, cmp) - begin(sa);
	int sa_ri = lower_bound(begin(sa) + sa_le, end(sa), 1, cmp) - begin(sa);
	return {sa_le, sa_ri, s_le, s_ri};
}
