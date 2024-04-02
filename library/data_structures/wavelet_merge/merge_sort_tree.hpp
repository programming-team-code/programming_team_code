/** @file */
#pragma once
#include "bool_presum.hpp"
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the merge sort tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
/**
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/mergeSortTree.cpp
 */
struct merge_sort_tree {
  int n;
  vi sorted;
  vector<bool_presum> bool_presums;
  /**
   * @param a array
   * @time O(n log n)
   * @space O(n + (n log n) / 64) for `bool_presums` vector
   */
  merge_sort_tree(const vi& a) : n(sz(a)), sorted(n), bool_presums(n, vector<bool>()) {
    vector<pair<int, bool>> cpy(n);
    transform(all(a), begin(cpy), [](int val) { return pair(val, 0); });
    build(cpy, 0, n, 1);
    transform(all(cpy), begin(sorted), [](auto& val) { return val.first; });
  }
  void build(vector<pair<int, bool>>& cpy, int tl, int tr, int u) {
    if (tr - tl <= 1) return;
    int tm = split(tl, tr);
    build(cpy, tl, tm, 2 * u);
    build(cpy, tm, tr, 2 * u + 1);
    for (int i = tl; i < tr; i++) cpy[i].second = i < tm;
    inplace_merge(begin(cpy) + tl, begin(cpy) + tm, begin(cpy) + tr);
    vector<bool> bools(tr - tl);
    transform(begin(cpy) + tl, begin(cpy) + tr, begin(bools), [](auto& val) { return val.second; });
    bool_presums[u] = bool_presum(bools);
  }
  /**
   * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
   * @returns number of indexes i such that le <= i < ri and x <= a[i] < y
   * @time O(log(n))
   * @space O(log(n)) for recursive stack
   */
  int rect_count(int le, int ri, int x, int y) {
    assert(0 <= le && le <= ri && ri <= n && x <= y);
    int xi = lower_bound(all(sorted), x) - begin(sorted);
    int yi = lower_bound(all(sorted), y) - begin(sorted);
    return rect_count_impl(le, ri, xi, yi, 0, n, 1);
  }
  int rect_count_impl(int le, int ri, int xi, int yi, int tl, int tr, int u) {
    if (ri <= tl || tr <= le) return 0;
    if (le <= tl && tr <= ri) return yi - xi;
    int tm = split(tl, tr), pl = bool_presums[u].popcount(xi), pr = bool_presums[u].popcount(yi);
    return rect_count_impl(le, ri, pl, pr, tl, tm, 2 * u) +
           rect_count_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * u + 1);
  }
  /**
   * @param x,y defines range of values [x, y)
   * @param k must satisfy 1 <= k <= number of indexes i such that x <= a[i] < y
   * @returns the kth smallest index i such that x <= a[i] < y
   *     - kth_smallest(x,y,1) returns the smallest index i such that x <= a[i] < y
   *     - kth_smallest(x,y,rect_count(0,n,x,y)) returns the largest index i such that x <= a[i] < y
   *     - kth_smallest(-INF,INF,k) returns (k - 1)
   * @time O(log(n))
   * @space O(log(n)) for recursive stack
   */
  int kth_smallest(int x, int y, int k) {
    int xi = lower_bound(all(sorted), x) - begin(sorted);
    int yi = lower_bound(all(sorted), y) - begin(sorted);
    assert(1 <= k && k <= yi - xi);
    return kth_smallest_impl(xi, yi, k, 0, n, 1);
  }
  int kth_smallest_impl(int xi, int yi, int k, int tl, int tr, int u) {
    if (tr - tl == 1) return tl;
    int tm = split(tl, tr), pl = bool_presums[u].popcount(xi), pr = bool_presums[u].popcount(yi);
    if (k <= pr - pl) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * u);
    return kth_smallest_impl(xi - pl, yi - pr, k - (pr - pl), tm, tr, 2 * u + 1);
  }
};
