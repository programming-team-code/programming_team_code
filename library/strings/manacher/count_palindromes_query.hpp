#pragma once
#include "../../data_structures/wavelet_merge/wavelet_tree.hpp"
#include "manacher.hpp"
//! @param l,r defines range [l, r)
//! @returns l + (l + 1) + ... + (r - 1)
//! @time O(1)
//! @space O(1)
ll sum_consecutive(int l, int r) {
  return ll(r - l) * (l + r - 1) / 2;
}
//! https://codeforces.com/blog/entry/63105#comment-470339
template<class T> struct count_pal_query {
  int n;
  vi man;
  wavelet_tree wt_le, wt_ri;
  //! @param s string/vector
  //! @time O(n log n)
  //! @space O(n log n) for wavelet trees
  count_pal_query(const T& s):
    n(sz(s)), man(manacher(s)), wt_le(man, 0, n),
    wt_ri(init()) {}
  wavelet_tree init() {
    vi right(sz(man));
    rep(i, 0, sz(man)) right[i] = i - man[i] + 1;
    return {right, 1, n + 1};
  }
  //! @param l,r defines substring [l, r) of s
  //! @returns number of palindromic substrings of
  //! s.substr(l, r - l)
  //! @time O(log n)
  //! @space O(1)
  ll count_pals(int l, int r) {
    assert(l < r);
    int man_le = 2 * l, man_ri = 2 * r - 1,
        man_mi = (man_le + man_ri) / 2;
    // sum over range [man_le, man_mi) of:
    //     i / 2 - max(man[i], l) + 1
    ll cnt =
      -1LL * wt_le.rect_count(man_le, man_mi, 0, l) * l;
    cnt -= wt_le.rect_sum(man_le, man_mi, l, n);
    cnt += sum_consecutive(l, man_mi / 2) +
      sum_consecutive(l, (man_mi + 1) / 2);
    cnt += man_mi - man_le;
    // sum over range [man_mi, man_ri) of:
    //     min(right[i], r) - (i + 1) / 2
    cnt +=
      ll(wt_ri.rect_count(man_mi, man_ri, r, n + 1)) * r;
    cnt += wt_ri.rect_sum(man_mi, man_ri, 1, r);
    cnt -= sum_consecutive((man_mi + 1) / 2, r) +
      sum_consecutive(man_mi / 2 + 1, r);
    return cnt;
  }
};
