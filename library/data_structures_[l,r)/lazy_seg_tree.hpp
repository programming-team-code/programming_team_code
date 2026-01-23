#pragma once
#include "seg_tree_midpoint.hpp"
struct seg_tree {
  ll op(ll vl, ll vr) { return vl + vr; }
  int n;
  vector<ll> tree, lazy;
  seg_tree(int n): n(n), tree(2 * n), lazy(n) {}
  seg_tree(const vi& a): n(sz(a)), tree(2 * n), lazy(n) {
    int pw2 = bit_ceil(size(a));
    rep(i, 0, n) tree[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--)
      tree[i] = op(tree[2 * i], tree[2 * i + 1]);
  }
  void apply(ll d, int tl, int tr, int v) {
    tree[v] += (tr - tl) * d;
    if (v < n) lazy[v] += d;
  }
  void push(int tl, int tm, int tr, int v) {
    if (lazy[v]) {
      apply(lazy[v], tl, tm, 2 * v);
      apply(lazy[v], tm, tr, 2 * v + 1);
      lazy[v] = 0;
    }
  }
  void update(int l, int r, ll d) {
    update(l, r, d, 0, n, 1);
  }
  void update(int l, int r, ll d, int tl, int tr, int v) {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) return apply(d, tl, tr, v);
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    update(l, r, d, tl, tm, 2 * v);
    update(l, r, d, tm, tr, 2 * v + 1);
    tree[v] = op(tree[2 * v], tree[2 * v + 1]);
  }
  ll query(int l, int r) { return query(l, r, 0, n, 1); }
  ll query(int l, int r, int tl, int tr, int v) {
    if (r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r) return tree[v];
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    return op(query(l, r, tl, tm, 2 * v),
      query(l, r, tm, tr, 2 * v + 1));
  }
#include "seg_tree_uncommon/find_first.hpp"
#include "seg_tree_uncommon/find_last.hpp"
};
