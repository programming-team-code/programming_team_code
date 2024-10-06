#pragma once
#include "lazy_seg_tree_inc_midpoint.hpp"
ll op(ll vl, ll vr) { return vl + vr; }
struct seg_tree_inc {
  int n;
  vector<ll> tree, lazy;
  seg_tree_inc(int a_n): n(a_n), tree(2 * n), lazy(n) {}
  seg_tree_inc(const vi& a):
    n(sz(a)), tree(2 * n), lazy(n) {
    int pw2 = 1;
    while (pw2 < n) pw2 *= 2;
    rep(i, 0, n) tree[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--)
      tree[i] = op(tree[2 * i], tree[2 * i + 1]);
  }
  void apply(ll change, int tl, int tr, int v) {
    tree[v] += (tr - tl + 1) * change;
    if (v < n) lazy[v] += change;
  }
  void push(int tl, int tm, int tr, int v) {
    if (lazy[v]) {
      apply(lazy[v], tl, tm, 2 * v);
      apply(lazy[v], tm + 1, tr, 2 * v + 1);
      lazy[v] = 0;
    }
  }
  void update(int le, int ri, ll change) { // [le, ri]
    update_impl(le, ri, change, 0, n - 1, 1);
  }
  void update_impl(int le, int ri, ll change, int tl,
    int tr, int v) {
    if (ri < tl || tr < le) return;
    if (le <= tl && tr <= ri)
      return apply(change, tl, tr, v);
    int tm = split_inc(tl, tr);
    push(tl, tm, tr, v);
    update_impl(le, ri, change, tl, tm, 2 * v);
    update_impl(le, ri, change, tm + 1, tr, 2 * v + 1);
    tree[v] = op(tree[2 * v], tree[2 * v + 1]);
  }
  ll query(int le, int ri) { // [le, ri]
    return query_impl(le, ri, 0, n - 1, 1);
  }
  ll query_impl(int le, int ri, int tl, int tr, int v) {
    if (ri < tl || tr < le) return 0;
    if (le <= tl && tr <= ri) return tree[v];
    int tm = split_inc(tl, tr);
    push(tl, tm, tr, v);
    return op(query_impl(le, ri, tl, tm, 2 * v),
      query_impl(le, ri, tm + 1, tr, 2 * v + 1));
  }
};
