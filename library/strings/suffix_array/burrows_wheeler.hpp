//! @file
#pragma once
#include "suffix_array.hpp"
const int mn = '0', cnt_let = 36;  // mn <= s[i] < mn + cnt_let; for lowercase letters: mn = 'a', cnt_let = 26
/**
 * Burrows Wheeler transform
 */
struct bwt {
  int n;
  char last;
  vector<array<int, cnt_let>> occ;
  array<int, cnt_let + 1> cnt{};
  /**
   * @code{.cpp}
         string s;
         auto [_, __, sa, sa_inv, lcp, ___] = suffix_array(s, 256);
         bwt bw(s, sa);
   * @endcode
   * @param s,sa a string and its suffix array
   * @time O(n * cnt_let)
   * @space O(n * cnt_let) for `occ` vector; it's possible to improve this
   *     to O(n * cnt_let / 64) https://codeforces.com/contest/963/submission/217802614
   */
  bwt(const string& s, const vi& sa) : n(sz(s)), last(empty(s) ? -1 : s.back() - mn), occ(n + 1) {
    rep(i, 0, n) {
      cnt[s[i] + 1 - mn]++;
      occ[i + 1] = occ[i];
      if (sa[i] == 0) continue;
      occ[i + 1][s[sa[i] - 1] - mn]++;
    }
    partial_sum(all(cnt), begin(cnt));
  }
  /**
   * @param t query string
   * @returns vectors `le`, `ri` where given `t_le` (0 <= t_le <= |t|) defines a suffix [t_le, |t|) of t:
   *     - for all i in [le[t_le], ri[t_le]): t.substr(t_le) == s.substr(sa[i], sz(t) - t_le)
   *     - `ri[t_le] - le[t_le]` is the # of matches of t.substr(t_le) in s.
   *     note: ri[t_le] - le[t_le] <= ri[t_le + 1] - le[t_le + 1]
   * @time O(|t|)
   * @space 2 O(|t|) vectors are allocated and returned
   */
  array<vi, 2> find_str(const string& t) {
    vi le(sz(t) + 1, 0), ri(sz(t) + 1, n);
    for (int i = sz(t) - 1; i >= 0; i--) {
      char c = t[i] - mn;
      le[i] = cnt[c] + occ[le[i + 1]][c] + (c == last && i < sz(t) - 1);
      ri[i] = cnt[c] + occ[ri[i + 1]][c] + (c == last);
    }
    return {le, ri};
  }
};
