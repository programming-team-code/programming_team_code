/** @file */
#pragma once
#include "../../data_structures/wavelet_merge/wavelet_tree.hpp"
#include "manacher.hpp"
/**
 * @param le,ri defines range [le, ri)
 * @returns le + (le + 1) + ... + (ri - 1)
 * @time O(1)
 * @space O(1)
 */
inline ll sum_consecutive(int le, int ri) {
  return 1LL * (ri - le) * (le + ri - 1) / 2;
}
/**
 * @see https://codeforces.com/blog/entry/63105#comment-470339
 */
template <class T> struct count_pal_query {
  int n;
  vi man;
  wavelet_tree wt_le, wt_ri;
  /**
   * @param s string/vector
   * @time O(n log n)
   * @space O(n log n) for wavelet trees
   */
  count_pal_query(const T& s) : n(sz(s)), man(manacher(s)), wt_le(man, 0, n), wt_ri(init()) {}
  wavelet_tree init() {
    vi right(sz(man));
    rep (i, 0, sz(man))
      right[i] = i - man[i] + 1;
    return {right, 1, n + 1};
  }
  /**
   * @param le,ri defines substring [le, ri) of s
   * @returns number of palindromic substrings of s.substr(le, ri - le)
   * @time O(log n)
   * @space O(1)
   */
  inline ll count_pals(int le, int ri) {
    assert(0 <= le && le < ri && ri <= n);
    int man_le = 2 * le, man_ri = 2 * ri - 1, man_mi = (man_le + man_ri) / 2;
    // sum over range [man_le, man_mi) of:
    //     i / 2 - max(man[i], le) + 1
    auto cnt = -1LL * wt_le.rect_count(man_le, man_mi, 0, le) * le;
    cnt -= wt_le.rect_sum(man_le, man_mi, le, n);
    cnt += sum_consecutive(le, man_mi / 2) + sum_consecutive(le, (man_mi + 1) / 2);
    cnt += man_mi - man_le;
    // sum over range [man_mi, man_ri) of:
    //     min(right[i], ri) - (i + 1) / 2
    cnt += 1LL * wt_ri.rect_count(man_mi, man_ri, ri, n + 1) * ri;
    cnt += wt_ri.rect_sum(man_mi, man_ri, 1, ri);
    cnt -= sum_consecutive((man_mi + 1) / 2, ri) + sum_consecutive(man_mi / 2 + 1, ri);
    return cnt;
  }
};
