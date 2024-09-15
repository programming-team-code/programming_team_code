//! @file
#pragma once
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html# preserving-the-history-of-its-values-persistent-segment-tree
 */
// NOLINTNEXTLINE(readability-identifier-naming)
struct PST {
  struct node {
    ll sum;
    int lch, rch;
    node(ll a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
  };
  int root_l, root_r;
  vi roots; /**< tree[roots[i]] = root node at version i */
  deque<node> tree;
  /**
   * @param a_root_l,a_root_r defines range [root_l, root_l) of root node, can be
   * negative
   * @time O(1)
   * @space O(1)
   */
  PST(int a_root_l, int a_root_r) : root_l(a_root_l), root_r(a_root_r), roots(1), tree(1, {0LL, 0, 0}) {}
  /**
   * @param idx,change does a[idx] += change
   * @param version which version to update. Each call to update creates a
   * new version. Initially there is a dummy version.
   * @time O(log(root_r - root_l))
   * @space O(log(root_r - root_l)) new nodes are pushed back onto `tree`; (and for recursion stack)
   */
  void update(int idx, ll change, int version) {
    roots.push_back(update_impl(idx, change, root_l, root_r, roots[version]));
  }
  int update_impl(int idx, ll change, int tl, int tr, int v) {
    if (tr - tl == 1) {
      tree.emplace_back(tree[v].sum + change, 0, 0);
      return sz(tree) - 1;
    }
    int tm = tl + (tr - tl) / 2;
    int lch = tree[v].lch;
    int rch = tree[v].rch;
    if (idx < tm)
      lch = update_impl(idx, change, tl, tm, lch);
    else
      rch = update_impl(idx, change, tm, tr, rch);
    tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
    return sz(tree) - 1;
  }
  /**
   * @param le, ri defines range [le, ri)
   * @param version which version to query
   * @returns a[le] + a[le + 1] + ... + a[ri - 1] during the `version`-th version
   * @time O(log(root_r - root_l))
   * @space O(log(root_r - root_l)) for recursion stack, no new nodes are allocated
   */
  ll query(int le, int ri, int version) {
    return query_impl(le, ri, root_l, root_r, roots[version]);
  }
  ll query_impl(int le, int ri, int tl, int tr, int v) {
    if (v == 0 || ri <= tl || tr <= le) return 0;
    if (le <= tl && tr <= ri) return tree[v].sum;
    int tm = tl + (tr - tl) / 2;
    return query_impl(le, ri, tl, tm, tree[v].lch) +
           query_impl(le, ri, tm, tr, tree[v].rch);
  }
};
