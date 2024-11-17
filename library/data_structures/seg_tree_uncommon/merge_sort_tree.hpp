#pragma once
#include "../lazy_seg_tree_midpoint.hpp"
struct merge_sort_tree {
  int n;
  vector<vi> tree;
  merge_sort_tree(const vi& a): n(sz(a)), tree(2 * n) {
    int pw2 = bit_ceil(size(a));
    rep(i, 0, n) tree[(i + pw2) % n + n] = {a[i]};
    for (int i = n - 1; i >= 1; i--) {
      tree[i].resize(
        sz(tree[2 * i]) + sz(tree[2 * i + 1]));
      ranges::merge(tree[2 * i], tree[2 * i + 1],
        begin(tree[i]));
    }
  }
  //! count of i in [l, r) such that a[i] in [vl, vr)
  //! @time O(log(n)^2)
  //! @space O(1)
  int query(int l, int r, int vl, int vr) {
    return query_impl(l, r, vl, vr, 0, n, 1);
  }
  int query_impl(int l, int r, int vl, int vr, int tl,
    int tr, int v) {
    if (r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r)
      return ranges::lower_bound(tree[v], vr) -
        ranges::lower_bound(tree[v], vl);
    int tm = split(tl, tr);
    return query_impl(l, r, vl, vr, tl, tm, 2 * v) +
      query_impl(l, r, vl, vr, tm, tr, 2 * v + 1);
  }
};
