//! https://codeforces.com/blog/entry/112755
//! @code
//!   int tm = split_inc(tl, tr);
//!   // [tl,tr] splits into [tl,tm] and [tm+1,tr]
//! @endcode
int split_inc(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl + 1);
  return min(tl + pw2 - 1, tr - pw2 / 2);
}
int64_t op_inc(int64_t vl, int64_t vr) { return vl + vr; }
struct seg_tree_inc {
  int n;
  vector<int64_t> tree, lazy;
  seg_tree_inc(int n): n(n), tree(2 * n), lazy(n) {}
  seg_tree_inc(const vector<int>& a):
    n(ssize(a)), tree(2 * n), lazy(n) {
    int pw2 = bit_ceil(size(a));
    for (int i = 0; i < n; i++)
      tree[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--)
      tree[i] = op_inc(tree[2 * i], tree[2 * i + 1]);
  }
  void apply(int64_t change, int tl, int tr, int v) {
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
  void update(int l, int r, int64_t change) { // [l, r]
    update_impl(l, r, change, 0, n - 1, 1);
  }
  void update_impl(int l, int r, int64_t change, int tl,
    int tr, int v) {
    if (r < tl || tr < l) return;
    if (l <= tl && tr <= r)
      return apply(change, tl, tr, v);
    int tm = split_inc(tl, tr);
    push(tl, tm, tr, v);
    update_impl(l, r, change, tl, tm, 2 * v);
    update_impl(l, r, change, tm + 1, tr, 2 * v + 1);
    tree[v] = op_inc(tree[2 * v], tree[2 * v + 1]);
  }
  int64_t query(int l, int r) { // [l, r]
    return query_impl(l, r, 0, n - 1, 1);
  }
  int64_t query_impl(int l, int r, int tl, int tr, int v) {
    if (r < tl || tr < l) return 0;
    if (l <= tl && tr <= r) return tree[v];
    int tm = split_inc(tl, tr);
    push(tl, tm, tr, v);
    return op_inc(query_impl(l, r, tl, tm, 2 * v),
      query_impl(l, r, tm + 1, tr, 2 * v + 1));
  }
};
