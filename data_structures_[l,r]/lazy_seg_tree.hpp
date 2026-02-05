//! https://codeforces.com/blog/entry/112755
//! @code
//!   int tm = split(tl, tr);
//!   // [tl,tr] splits into [tl,tm] and [tm+1,tr]
//! @endcode
int split(int tl, int tr) {
  int pw2 = bit_floor(tr - tl + 1u);
  return min(tl + pw2 - 1, tr - pw2 / 2);
}
int64_t op(int64_t vl, int64_t vr) { return vl + vr; }
struct seg_tree {
  int n;
  vector<int64_t> tree, lazy;
  seg_tree(int n): n(n), tree(2 * n), lazy(n) {}
  seg_tree(const vector<int>& a):
    n(ssize(a)), tree(2 * n), lazy(n) {
    int pw2 = bit_ceil(size(a));
    for (int i = 0; i < n; i++)
      tree[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--)
      tree[i] = op(tree[2 * i], tree[2 * i + 1]);
  }
  void apply(int64_t d, int tl, int tr, int v) {
    tree[v] += (tr - tl + 1) * d;
    if (v < n) lazy[v] += d;
  }
  void push(int tl, int tm, int tr, int v) {
    if (lazy[v]) {
      apply(lazy[v], tl, tm, 2 * v);
      apply(lazy[v], tm + 1, tr, 2 * v + 1);
      lazy[v] = 0;
    }
  }
  void update(int l, int r, int64_t d) {
    update(l, r, d, 0, n - 1, 1);
  }
  void update(int l, int r, int64_t d, int tl, int tr,
    int v) {
    if (r < tl || tr < l) return;
    if (l <= tl && tr <= r) return apply(d, tl, tr, v);
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    update(l, r, d, tl, tm, 2 * v);
    update(l, r, d, tm + 1, tr, 2 * v + 1);
    tree[v] = op(tree[2 * v], tree[2 * v + 1]);
  }
  int64_t query(int l, int r) {
    return query(l, r, 0, n - 1, 1);
  }
  int64_t query(int l, int r, int tl, int tr, int v) {
    if (r < tl || tr < l) return 0;
    if (l <= tl && tr <= r) return tree[v];
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    return op(query(l, r, tl, tm, 2 * v),
      query(l, r, tm + 1, tr, 2 * v + 1));
  }
};
