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
    node(ll sum, int lch, int rch):
      sum(sum), lch(lch), rch(rch) {}
  };
  int root_l, root_r;
  vi roots;
  deque<node> tree;
  PST(int root_l, int root_r):
    root_l(root_l), root_r(root_r), roots(1),
    tree(1, {0LL, 0, 0}) {}
  void update(int idx, ll change, int version) {
    roots.push_back(
      update(idx, change, root_l, root_r, roots[version]));
  }
  int update(int idx, ll change, int tl, int tr, int v) {
    if (tr - tl == 1) {
      tree.emplace_back(tree[v].sum + change, 0, 0);
      return sz(tree) - 1;
    }
    int tm = tl + (tr - tl) / 2;
    int lch = tree[v].lch;
    int rch = tree[v].rch;
    if (idx < tm) lch = update(idx, change, tl, tm, lch);
    else rch = update(idx, change, tm, tr, rch);
    tree.emplace_back(tree[lch].sum + tree[rch].sum, lch,
      rch);
    return sz(tree) - 1;
  }
  ll query(int l, int r, int version) { // [l, r)
    return query(l, r, root_l, root_r, roots[version]);
  }
  ll query(int l, int r, int tl, int tr, int v) {
    if (v == 0 || r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r) return tree[v].sum;
    int tm = tl + (tr - tl) / 2;
    return query(l, r, tl, tm, tree[v].lch) +
      query(l, r, tm, tr, tree[v].rch);
  }
};
