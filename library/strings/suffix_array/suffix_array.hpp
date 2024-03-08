/** @file */
#pragma once
#include "../../data_structures/rmq.hpp" /**< only needed for lcp_query */
#include "find/match.hpp" /**< only needed for find functions */
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 */
template <class T> struct suffix_array {
	T s;
	int n;
	/**
	 * suffixes of "banana":
	 * 0 banana 3
	 * 1 anana  2
	 * 2 nana   5
	 * 3 ana    1
	 * 4 na     4
	 * 5 a      0
	 *
	 * 5 a      0
	 *   |
	 * 3 ana    1
	 *   |||
	 * 1 anana  2
	 *
	 * 0 banana 3
	 *
	 * 4 na     4
	 *   ||
	 * 2 nana   5
	 *
	 * sa = {5, 3, 1, 0, 4, 2}
	 * sa_inv = {3, 2, 5, 1, 4, 0} (sa[sa_inv[i]] == i, sa_inv[sa[i]] == i)
	 * lcp = {1, 3, 0, 0, 2}
	 * @{
	 */
	vector<int> sa, sa_inv, lcp;
	/** @} */
	/**
	 * @code{.cpp}
	       string s;
	       suffix_array sf_a(s, 256);
	       auto [_, __, sa, sa_inv, lcp, ___] = suffix_array(s, 256);
	       // or
	       vector<int> a;
	       suffix_array sf_a(a, 100'005);
	 * @endcode
	 * @param a_s,max_val string/array with 0 <= a_s[i] < max_val
	 * @time O((n log n) + max_val)
	 * @space vectors `sa`, `sa_inv`, `lcp` are O(n); vector `freq` is
	 * O(max_val) and is allocated temporarily
	 */
	suffix_array(const T& a_s, int max_val) : s(a_s), n(ssize(s)), sa(n), sa_inv(begin(s), end(s)), lcp(max(0, n - 1)) {
		vector<int> tmp(n);
		iota(begin(sa), end(sa), 0);
		for (int ln = 0; ln < n; ln = max(1, 2 * ln)) {
			iota(begin(tmp), begin(tmp) + ln, n - ln);
			copy_if(begin(sa), end(sa), begin(tmp) + ln, [&](int& val) {return (val -= ln) >= 0;});
			vector<int> freq(max_val);
			for (int val : sa_inv) freq[val]++;
			partial_sum(begin(freq), end(freq), begin(freq));
			for_each(rbegin(tmp), rend(tmp), [&](int t) {sa[--freq[sa_inv[t]]] = t;});
			swap(sa_inv, tmp);
			max_val = 1, sa_inv[sa[0]] = 0;
			auto prev_inv = [&](int i) {return pair(tmp[i], i + ln < n ? tmp[i + ln] : -1);};
			for (int i = 1; i < n; i++) {
				max_val += prev_inv(sa[i - 1]) != prev_inv(sa[i]);
				sa_inv[sa[i]] = max_val - 1;
			}
			if (max_val == n) break;
		}
		for (int i = 0, sz = 0; i < n; i++) {
			if (sz > 0) sz--;
			if (sa_inv[i] == 0) continue;
			for (int j = sa[sa_inv[i] - 1]; max(i, j) + sz < n && s[i + sz] == s[j + sz];) sz++;
			lcp[sa_inv[i] - 1] = sz;
		}
	}
#include "lcp_query.hpp"
#include "compare/compare_substrings.hpp"
#include "compare/compare_suffixes.hpp"
#include "find/find_string_bs.hpp"
#include "find/find_substrings_concatenated.hpp"
};
