/** @file */
#pragma once
#include "../suffix_array.hpp"
const int mn = '0', max_val = 36; // mn <= s[i] < mn + max_val; for lowercase letters: mn = 'a', max_val = 26
/**
 * Burrows Wheeler transform
 */
struct find_bwt {
	int n;
	char last;
	vector<array<int, max_val>> occ;
	array < int, max_val + 1 > cnt{};
	/**
	 * @code{.cpp}
	       string s;
	       auto [sa, sa_inv] = get_sa(s, 256);
	       find_bwt fb(s, sa);
	 * @endcode
	 * @param s,sa a string and its suffix array
	 * @time O(n * max_val)
	 * @space O(n * max_val) for `occ` vector; it's possible to improve this
	 *     to O(n * max_val / 64) https://codeforces.com/contest/963/submission/217802614
	 */
	find_bwt(const string& s, const vector<int>& sa) : n(ssize(s)), last(empty(s) ? -1 : s.back() - mn), occ(n + 1) {
		for (int i = 0; i < n; i++) {
			cnt[s[i] + 1 - mn]++;
			occ[i + 1] = occ[i];
			if (sa[i] == 0) continue;
			occ[i + 1][s[sa[i] - 1] - mn]++;
		}
		partial_sum(begin(cnt), end(cnt), begin(cnt));
	}
	/**
	 * @code{.cpp}
	       string t;
	       auto [le, ri] = fb.find_str(t);
	 * @endcode
	 * @param t query string
	 * @returns vectors `le`, `ri` where given `t_le` (0 <= t_le <= |t|) defines a suffix [t_le, |t|) of t:
	 *     - for all i in [le[t_le], ri[t_le]): t.substr(t_le) == s.substr(sa[i], ssize(t) - t_le)
	 *     - `ri[t_le] - le[t_le]` is the # of matches of t.substr(t_le) in s.
	 *     note: ri[t_le] - le[t_le] <= ri[t_le + 1] - le[t_le + 1]
	 * @time O(|t|)
	 * @space 2 O(|t|) vectors are allocated and returned
	 */
	array<vector<int>, 2> find_str(const string& t) {
		vector<int> le(ssize(t) + 1, 0), ri(ssize(t) + 1, n);
		for (int i = ssize(t) - 1; i >= 0; i--) {
			char c = t[i] - mn;
			le[i] = cnt[c] + occ[le[i + 1]][c] + (c == last && i < ssize(t) - 1);
			ri[i] = cnt[c] + occ[ri[i + 1]][c] + (c == last);
		}
		return {le, ri};
	}
};
