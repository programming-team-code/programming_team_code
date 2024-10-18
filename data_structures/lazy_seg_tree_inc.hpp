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
  seg_tree_inc(int a_n): n(a_n), tree(2 * n), lazy(n) {}
  seg_tree_inc(const vector<int>& a):
    n((int)size(a)), tree(2 * n), lazy(n) {
    int pw2 = 1;
    while (pw2 < n) pw2 *= 2;
    for (int i = 0; i < (n); i++)
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
  void update(int le, int ri, int64_t change) { // [le, ri]
    update_impl(le, ri, change, 0, n - 1, 1);
  }
  void update_impl(int le, int ri, int64_t change, int tl,
    int tr, int v) {
    if (ri < tl || tr < le) return;
    if (le <= tl && tr <= ri)
      return apply(change, tl, tr, v);
    int tm = split_inc(tl, tr);
    push(tl, tm, tr, v);
    update_impl(le, ri, change, tl, tm, 2 * v);
    update_impl(le, ri, change, tm + 1, tr, 2 * v + 1);
    tree[v] = op_inc(tree[2 * v], tree[2 * v + 1]);
  }
  int64_t query(int le, int ri) { // [le, ri]
    return query_impl(le, ri, 0, n - 1, 1);
  }
  int64_t query_impl(int le, int ri, int tl, int tr,
    int v) {
    if (ri < tl || tr < le) return 0;
    if (le <= tl && tr <= ri) return tree[v];
    int tm = split_inc(tl, tr);
    push(tl, tm, tr, v);
    return op_inc(query_impl(le, ri, tl, tm, 2 * v),
      query_impl(le, ri, tm + 1, tr, 2 * v + 1));
  }
};
