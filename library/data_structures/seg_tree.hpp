/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the segment tree a complete
 * binary tree
 */
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
ll op(ll vl, ll vr) { return vl + vr; }
/**
 * root is at tree[1]
 * internal nodes are [1, n)
 * leaf nodes are [n, 2 * n), but rotated such that a[0] is at tree[pw2]
 *     where pw2 is the only power of 2 such that n <= pw2 < 2 * n
 */
struct seg_tree {
  int n;
  vector<ll> tree, lazy;
  seg_tree(int a_n) : n(a_n), tree(2 * n), lazy(n) {}
  seg_tree(const vi& a) : n(sz(a)), tree(2 * n), lazy(n) {
    int pw2 = 1;
    while (pw2 < n) pw2 *= 2;
    rep(i, 0, n) tree[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--) tree[i] = op(tree[2 * i], tree[2 * i + 1]);
  }
  void apply(ll change, int tl, int tr, int u) {
    tree[u] += (tr - tl) * change;
    if (u < n) lazy[u] += change;
  }
  void push(int tl, int tm, int tr, int u) {
    if (lazy[u]) {
      apply(lazy[u], tl, tm, 2 * u);
      apply(lazy[u], tm, tr, 2 * u + 1);
      lazy[u] = 0;
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  void update(int le, int ri, ll change) { update_impl(le, ri, change, 0, n, 1); }
  void update_impl(int le, int ri, ll change, int tl, int tr, int u) {
    if (ri <= tl || tr <= le) return;
    if (le <= tl && tr <= ri) return apply(change, tl, tr, u);
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    update_impl(le, ri, change, tl, tm, 2 * u);
    update_impl(le, ri, change, tm, tr, 2 * u + 1);
    tree[u] = op(tree[2 * u], tree[2 * u + 1]);
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  ll query(int le, int ri) { return query_impl(le, ri, 0, n, 1); }
  ll query_impl(int le, int ri, int tl, int tr, int u) {
    if (ri <= tl || tr <= le) return 0;
    if (le <= tl && tr <= ri) return tree[u];
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    return op(query_impl(le, ri, tl, tm, 2 * u),
              query_impl(le, ri, tm, tr, 2 * u + 1));
  }
#include "seg_tree_uncommon/find_first.hpp"
#include "seg_tree_uncommon/find_last.hpp"
};
