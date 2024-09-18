#pragma once
#include "bool_presum.hpp"
#include "bool_bit.hpp"
//! https://codeforces.com/blog/entry/112755
//! @param tl,tr defines range [tl, tr)
//! @returns split point of range which makes the wavelet
//! tree a complete binary tree
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
//! https://ioinformatics.org/journal/v10_2016_19_37.pdf
//! https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/waveletTree.cpp
struct wavelet_tree_updates {
  int n, minv, maxv;
  vector<bool_presum> bool_presums;
  vector<bool_bit> bool_bits;
  //! @code
  //!     vi a;
  //!     ...
  //!     vi sorted(a);
  //!     sort(all(sorted));
  //!     sorted.erase(unique(all(sorted)), end(sorted));
  //!     for (int& num : a) num = lower_bound(all(sorted),
  //!     num) - begin(sorted); wavelet_tree_updates wtu(a,
  //!     0, sz(sorted), vector<bool>(sz(a), 1));
  //! @endcode
  //! @param a,a_minv,a_maxv must satisfy minv <= a[i] < maxv
  //! @param active active[i] == 1 iff index i is initially
  //! active
  //! @time O((maxv - minv) + n * log(maxv - minv))
  //! @space O((maxv - minv) + n * log(maxv - minv) / 64) for
  //! `bool_presums` and for `bool_bits`
  wavelet_tree_updates(const vi& a, int a_minv, int a_maxv,
    const vector<bool>& active):
    n(sz(a)), minv(a_minv), maxv(a_maxv),
    bool_presums(maxv - minv, vector<bool>()),
    bool_bits(2 * (maxv - minv), vector<bool>()) {
    vector<pair<int, bool>> cpy(n);
    transform(all(a), begin(active), begin(cpy),
      [](int x, bool y) { return pair(x, y); });
    build(cpy, 0, n, minv, maxv, 1);
  }
  void build(vector<pair<int, bool>>& cpy, int le, int ri,
    int tl, int tr, int v) {
    vector<bool> bools(ri - le);
    transform(begin(cpy) + le, begin(cpy) + ri, begin(bools),
      [](auto& p) { return p.second; });
    bool_bits[v] = bool_bit(bools);
    if (tr - tl <= 1) return;
    int tm = split(tl, tr);
    auto low = [&](auto& p) { return p.first < tm; };
    transform(begin(cpy) + le, begin(cpy) + ri, begin(bools),
      low);
    bool_presums[v] = bool_presum(bools);
    int mi = stable_partition(begin(cpy) + le,
               begin(cpy) + ri, low) -
      begin(cpy);
    build(cpy, le, mi, tl, tm, 2 * v);
    build(cpy, mi, ri, tm, tr, 2 * v + 1);
  }
  //! @param i index
  //! @param is_active we want to set active[i] = is_active
  //! @time O(log(maxv - minv) * log(n / 64))
  //! @space O(log(maxv - minv)) for recursive stack
  void set_active(int i, bool is_active) {
    if (bool_bits[1].on(i) == is_active) return;
    set_active_impl(i, is_active, minv, maxv, 1);
  }
  void set_active_impl(int i, bool is_active, int tl, int tr,
    int v) {
    bool_bits[v].set(i, is_active);
    if (tr - tl == 1) return;
    int tm = split(tl, tr), pi = bool_presums[v].popcount(i);
    if (bool_presums[v].on(i))
      return set_active_impl(pi, is_active, tl, tm, 2 * v);
    set_active_impl(i - pi, is_active, tm, tr, 2 * v + 1);
  }
  //! @param le,ri,x,y defines rectangle: indexes in [le,
  //! ri), numbers in [x, y)
  //! @returns number of active indexes i such that le <= i <
  //! ri and x <= a[i] < y
  //! @time O(log(maxv - minv) * log(n / 64))
  //! @space O(log(maxv - minv)) for recursive stack
  int rect_count(int le, int ri, int x, int y) {
    return rect_count_impl(le, ri, x, y, minv, maxv, 1);
  }
  int rect_count_impl(int le, int ri, int x, int y, int tl,
    int tr, int v) {
    if (y <= tl || tr <= x) return 0;
    if (x <= tl && tr <= y)
      return bool_bits[v].popcount(le, ri);
    int tm = split(tl, tr),
        pl = bool_presums[v].popcount(le),
        pr = bool_presums[v].popcount(ri);
    return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
      rect_count_impl(le - pl, ri - pr, x, y, tm, tr,
        2 * v + 1);
  }
  //! @param le,ri defines range [le, ri)
  //! @param k must satisfy 1 <= k <= # active indexes in
  //! [le, ri)
  //! @returns kth smallest active number in range.
  //!     - kth_smallest(le,ri,1) returns the smallest active
  //!     number
  //!     - kth_smallest(le,ri,rect_count(le,ri,-INF,INF))
  //!     returns the largest active number
  //! @time O(log(maxv - minv) * log(n / 64))
  //! @space O(log(maxv - minv)) for recursive stack
  int kth_smallest(int le, int ri, int k) {
    return kth_smallest_impl(le, ri, k, minv, maxv, 1);
  }
  int kth_smallest_impl(int le, int ri, int k, int tl,
    int tr, int v) {
    if (tr - tl == 1) return tl;
    int tm = split(tl, tr),
        pl = bool_presums[v].popcount(le),
        pr = bool_presums[v].popcount(ri);
    int cnt_left = bool_bits[2 * v].popcount(pl, pr);
    if (k <= cnt_left)
      return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
    return kth_smallest_impl(le - pl, ri - pr, k - cnt_left,
      tm, tr, 2 * v + 1);
  }
};
