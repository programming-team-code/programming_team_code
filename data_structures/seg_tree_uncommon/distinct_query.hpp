//! https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//! @code
//!   PST pst(root_l, root_r);
//! @endcode
//! root's range is [root_l, root_r)
//! pst.tree[pst.roots[i]] = root at version i
//! @time O(q * log n), n = root_r-root_l
//! @space O(q * log n)
struct PST {
  struct node {
    int64_t sum;
    int lch, rch;
    node(int64_t sum, int lch, int rch):
      sum(sum), lch(lch), rch(rch) {}
  };
  int root_l, root_r;
  vector<int> roots;
  deque<node> tree;
  PST(int root_l, int root_r):
    root_l(root_l), root_r(root_r), roots(1),
    tree(1, {0LL, 0, 0}) {}
  void update(int idx, int64_t change, int version) {
    roots.push_back(update_impl(idx, change, root_l,
      root_r, roots[version]));
  }
  int update_impl(int idx, int64_t change, int tl, int tr,
    int v) {
    if (tr - tl == 1) {
      tree.emplace_back(tree[v].sum + change, 0, 0);
      return ssize(tree) - 1;
    }
    int tm = tl + (tr - tl) / 2;
    int lch = tree[v].lch;
    int rch = tree[v].rch;
    if (idx < tm)
      lch = update_impl(idx, change, tl, tm, lch);
    else rch = update_impl(idx, change, tm, tr, rch);
    tree.emplace_back(tree[lch].sum + tree[rch].sum, lch,
      rch);
    return ssize(tree) - 1;
  }
  int64_t query(int l, int r, int version) { // [l, r)
    return query_impl(l, r, root_l, root_r,
      roots[version]);
  }
  int64_t query_impl(int l, int r, int tl, int tr, int v) {
    if (v == 0 || r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r) return tree[v].sum;
    int tm = tl + (tr - tl) / 2;
    return query_impl(l, r, tl, tm, tree[v].lch) +
      query_impl(l, r, tm, tr, tree[v].rch);
  }
};
//! https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
struct distinct_query {
  int n;
  PST pst;
  //! @param a static array; can't handle updates
  //! @time O(n log n)
  //! @space O(n log n)
  distinct_query(const vector<int>& a):
    n(ssize(a)), pst(0, n + 1) {
    map<int, int> last_idx;
    for (int i = 0; i < n; i++) {
      int& idx = last_idx[a[i]];
      pst.update(idx, 1, i);
      idx = i + 1;
    }
  }
  //! @param l,r defines range [l, r)
  //! @returns number of distinct elements in range;
  //! query(i, i) returns 0.
  //! @time O(log n)
  //! @space O(log n)
  int query(int l, int r) {
    return pst.query(0, l + 1, r) - pst.query(0, l + 1, l);
  }
};
