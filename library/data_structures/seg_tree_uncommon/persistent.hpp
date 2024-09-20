#pragma once
//! https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//! @code
//!   PST pst(root_l, root_r);
//! @endcode
//! root's range is [root_l, root_r)
//! pst.tree[pst.roots[i]] = root at version i
//! @time O(q * log n), n = root_r-root_l
//! @space O(q * log n)
// NOLINTNEXTLINE(readability-identifier-naming)
struct PST {
  struct node {
    ll sum;
    int lch, rch;
    node(ll a_sum, int a_lch, int a_rch):
      sum(a_sum), lch(a_lch), rch(a_rch) {}
  };
  int root_l, root_r;
  vi roots;
  deque<node> tree;
  PST(int a_root_l, int a_root_r):
    root_l(a_root_l), root_r(a_root_r), roots(1),
    tree(1, {0LL, 0, 0}) {}
  void update(int idx, ll change, int version) {
    roots.push_back(update_impl(idx, change, root_l,
      root_r, roots[version]));
  }
  int update_impl(int idx, ll change, int tl, int tr,
    int v) {
    if (tr - tl == 1) {
      tree.emplace_back(tree[v].sum + change, 0, 0);
      return sz(tree) - 1;
    }
    int tm = tl + (tr - tl) / 2;
    int lch = tree[v].lch;
    int rch = tree[v].rch;
    if (idx < tm)
      lch = update_impl(idx, change, tl, tm, lch);
    else rch = update_impl(idx, change, tm, tr, rch);
    tree.emplace_back(tree[lch].sum + tree[rch].sum, lch,
      rch);
    return sz(tree) - 1;
  }
  ll query(int le, int ri, int version) { // [le, ri)
    return query_impl(le, ri, root_l, root_r,
      roots[version]);
  }
  ll query_impl(int le, int ri, int tl, int tr, int v) {
    if (v == 0 || ri <= tl || tr <= le) return 0;
    if (le <= tl && tr <= ri) return tree[v].sum;
    int tm = tl + (tr - tl) / 2;
    return query_impl(le, ri, tl, tm, tree[v].lch) +
      query_impl(le, ri, tm, tr, tree[v].rch);
  }
};
