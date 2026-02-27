//! https://codeforces.com/blog/entry/112755
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
struct merge_sort_tree {
  int n;
  vector<vector<int>> tree;
  merge_sort_tree(const vector<int>& a):
    n(ssize(a)), tree(2 * n) {
    int pw2 = bit_ceil(size(a));
    for (int i = 0; i < n; i++)
      tree[(i + pw2) % n + n] = {a[i]};
    for (int i = n - 1; i >= 1; i--)
      ranges::merge(tree[2 * i], tree[2 * i + 1],
        back_inserter(tree[i]));
  }
  //! count of i in [l, r) such that a[i] in [vl, vr)
  //! @time O(log(n)^2)
  //! @space O(1)
  int query(int l, int r, int vl, int vr) {
    return query(l, r, vl, vr, 0, n, 1);
  }
  int query(int l, int r, int vl, int vr, int tl, int tr,
    int v) {
    if (r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r)
      return ranges::lower_bound(tree[v], vr) -
        ranges::lower_bound(tree[v], vl);
    int tm = split(tl, tr);
    return query(l, r, vl, vr, tl, tm, 2 * v) +
      query(l, r, vl, vr, tm, tr, 2 * v + 1);
  }
};
