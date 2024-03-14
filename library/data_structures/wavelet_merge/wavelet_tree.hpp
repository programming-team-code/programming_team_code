/** @file */
#pragma once
#include "bool_presum.hpp"
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the wavelet tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
/**
 * @see https://ioinformatics.org/journal/v10_2016_19_37.pdf
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/waveletTree.cpp
 */
struct wavelet_tree {
  int n, minv, maxv;
  vector<bool_presum> bool_presums;
  vector<vector<int64_t>> presums;
  /**
   * @code{.cpp}
         vector<int> a;
         ...
         vector<int> sorted(a);
         sort(begin(sorted), end(sorted));
         sorted.erase(unique(begin(sorted), end(sorted)), end(sorted));
         for (int& val : a) val = lower_bound(begin(sorted), end(sorted), val) - begin(sorted);
         wavelet_tree wt(a, 0, ssize(sorted));
   * @endcode
   * @param a,a_minv,a_maxv must satisfy minv <= a[i] < maxv
   * @time O((maxv - minv) + n * log(maxv - minv))
   * @space O((maxv - minv) + n * log(maxv - minv) / 64) for `bool_presums`
   *        O((maxv - minv) + n * log(maxv - minv))      for `presums`
   */
  wavelet_tree(vector<int> a, int a_minv, int a_maxv) : n(ssize(a)), minv(a_minv), maxv(a_maxv), bool_presums(maxv - minv, vector<bool>()), presums(maxv - minv) {
    build(a, 0, n, minv, maxv, 1);
  }
  void build(vector<int>& a, int le, int ri, int tl, int tr, int u) {
    if (tr - tl <= 1) return;
    int tm = split(tl, tr);
    auto low = [&](int val) { return val < tm; };
    vector<bool> bools(ri - le);
    transform(begin(a) + le, begin(a) + ri, begin(bools), low);
    bool_presums[u] = bool_presum(bools);
    presums[u].resize(ri - le + 1);
    inclusive_scan(begin(a) + le, begin(a) + ri, begin(presums[u]) + 1, plus<int64_t>(), 0LL);
    int mi = stable_partition(begin(a) + le, begin(a) + ri, low) - begin(a);
    build(a, le, mi, tl, tm, 2 * u);
    build(a, mi, ri, tm, tr, 2 * u + 1);
  }
  /**
   * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
   * @returns number of indexes i such that le <= i < ri and x <= a[i] < y
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int rect_count(int le, int ri, int x, int y) {
    assert(0 <= le && le <= ri && ri <= n && x <= y);
    return rect_count_impl(le, ri, x, y, minv, maxv, 1);
  }
  int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int u) {
    if (y <= tl || tr <= x) return 0;
    if (x <= tl && tr <= y) return ri - le;
    int tm = split(tl, tr), pl = bool_presums[u].popcount(le), pr = bool_presums[u].popcount(ri);
    return rect_count_impl(pl, pr, x, y, tl, tm, 2 * u) +
           rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * u + 1);
  }
  /**
   * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
   * @returns sum of values a[i] such that le <= i < ri and x <= a[i] < y
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int64_t rect_sum(int le, int ri, int x, int y) {
    assert(0 <= le && le <= ri && ri <= n && x <= y);
    return rect_sum_impl(le, ri, x, y, minv, maxv, 1);
  }
  int64_t rect_sum_impl(int le, int ri, int x, int y, int tl, int tr, int u) {
    if (y <= tl || tr <= x) return 0;
    if (x <= tl && tr <= y) return (tr - tl == 1 ? 1LL * tl * (ri - le) : presums[u][ri] - presums[u][le]);
    int tm = split(tl, tr), pl = bool_presums[u].popcount(le), pr = bool_presums[u].popcount(ri);
    return rect_sum_impl(pl, pr, x, y, tl, tm, 2 * u) +
           rect_sum_impl(le - pl, ri - pr, x, y, tm, tr, 2 * u + 1);
  }
  /**
   * @param le,ri defines range [le, ri)
   * @param k must satisfy 1 <= k <= ri - le
   * @returns kth smallest number in range.
   *     - kth_smallest(le,ri,1) returns the min
   *     - kth_smallest(le,ri,(ri-le)) returns the max
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int kth_smallest(int le, int ri, int k) {
    assert(0 <= le && ri <= n);
    assert(1 <= k && k <= ri - le);
    return kth_smallest_impl(le, ri, k, minv, maxv, 1);
  }
  int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int u) {
    if (tr - tl == 1) return tl;
    int tm = split(tl, tr), pl = bool_presums[u].popcount(le), pr = bool_presums[u].popcount(ri);
    if (k <= pr - pl) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * u);
    return kth_smallest_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * u + 1);
  }
  /**
   * @param le,ri defines range [le, ri)
   * @param k must satisfy 0 <= k <= ri - le
   * @returns the sum of the k smallest numbers in range.
   *     - kth_sum(le,ri,0) returns 0
   *     - kth_sum(le,ri,1) returns the min
   *     - kth_sum(le,ri,(ri-le)) returns the sum
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int64_t kth_sum(int le, int ri, int k) {
    assert(0 <= le && ri <= n);
    assert(0 <= k && k <= ri - le);
    return kth_sum_impl(le, ri, k, minv, maxv, 1);
  }
  int64_t kth_sum_impl(int le, int ri, int k, int tl, int tr, int u) {
    if (tr - tl == 1) return 1LL * k * tl;
    int tm = split(tl, tr), pl = bool_presums[u].popcount(le), pr = bool_presums[u].popcount(ri);
    if (k <= pr - pl) return kth_sum_impl(pl, pr, k, tl, tm, 2 * u);
    auto sum_left = (tm - tl == 1 ? 1LL * tl * (pr - pl) : presums[2 * u][pr] - presums[2 * u][pl]);
    return sum_left + kth_sum_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * u + 1);
  }
};
