//! https://codeforces.com/blog/entry/112755
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
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
  void update(int l, int r, int64_t d) {
    update(l, r, d, 0, n, 1);
  }
  void update(int l, int r, int64_t d, int tl, int tr,
    int v) {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) return apply(d, tl, tr, v);
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    update(l, r, d, tl, tm, 2 * v);
    update(l, r, d, tm, tr, 2 * v + 1);
    tree[v] = op(tree[2 * v], tree[2 * v + 1]);
  }
  int64_t query(int l, int r) {
    return query(l, r, 0, n, 1);
  }
  int64_t query(int l, int r, int tl, int tr, int v) {
    if (r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r) return tree[v];
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    return op(query(l, r, tl, tm, 2 * v),
      query(l, r, tm, tr, 2 * v + 1));
  }
  //! @code
  //!   seg_tree st(n);
  //!   st.find_first(l, r, [&](ll x, int tl, int tr) ->
  //!   bool {
  //!   });
  //! @endcode
  //! @param l,r defines range [l, r)
  //! @param f defines a function that returns 1 if the
  //! subtree contains an element that satisfies the
  //! condition
  //!
  //! guarantee: `f` is called in order on the subtrees
  //! (tls are weakly increasing) and at most once on each
  //! subtree
  //!
  //! if `f` returns 1 then every subsequent call to `f`
  //! will be a subtree of the previous call; otherwise the
  //! next call will be a subsequent range of the previous
  //! range
  //!
  //! seg_tree_find.test.cpp for more details
  //!
  //! @returns the index of the first element in the range
  //! that satisfies the condition described in `f`, if no
  //! such element exists then `r` is returned
  //! @time O(log(n))
  //! @space O(log(n)) for recursion stack
  int find_first(int l, int r, const auto& f) {
    return find_first_in_range(l, r, f, 0, n, 1);
  }
  //! invariant: f(tree[v], tl, tr) is 1
  int find_first_in_subtree(const auto& f, int tl, int tr,
    int v) {
    if (v >= n) return tl;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    if (f(tree[2 * v], tl, tm))
      return find_first_in_subtree(f, tl, tm, 2 * v);
    return find_first_in_subtree(f, tm, tr, 2 * v + 1);
  }
  int find_first_in_range(int l, int r, const auto& f,
    int tl, int tr, int v) {
    if (r <= tl || tr <= l) return r;
    if (l <= tl && tr <= r)
      return f(tree[v], tl, tr)
        ? find_first_in_subtree(f, tl, tr, v)
        : r;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    int res = find_first_in_range(l, r, f, tl, tm, 2 * v);
    if (res < r) return res;
    return find_first_in_range(l, r, f, tm, tr, 2 * v + 1);
  }
  //! @code
  //!   seg_tree st(n);
  //!   st.find_last(l, r, [&](ll x, int tl, int tr) ->
  //!   bool {
  //!   });
  //! @endcode
  //! @param l,r defines range [l, r)
  //! @param f defines a function that returns 1 if the
  //! subtree contains an element that satisfies the
  //! condition
  //!
  //! guarantee: `f` is called in order on the subtrees
  //! (trs are weakly decreasing) and at most once on each
  //! subtree
  //!
  //! if `f` returns 1 then every subsequent call to `f`
  //! will be a subtree of the previous call; otherwise the
  //! next call will be a subsequent range of the previous
  //! range
  //!
  //! seg_tree_find.test.cpp for more details
  //!
  //! @returns the index of the last element in the range
  //! that satisfies the condition described in `f`, if no
  //! such element exists then (l - 1) is returned
  //! @time O(log(n))
  //! @space O(log(n)) for recursion stack
  int find_last(int l, int r, const auto& f) {
    return find_last_in_range(l, r, f, 0, n, 1);
  }
  //! invariant: f(tree[v], tl, tr) is 1
  int find_last_in_subtree(const auto& f, int tl, int tr,
    int v) {
    if (v >= n) return tl;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    if (f(tree[2 * v + 1], tm, tr))
      return find_last_in_subtree(f, tm, tr, 2 * v + 1);
    return find_last_in_subtree(f, tl, tm, 2 * v);
  }
  int find_last_in_range(int l, int r, const auto& f,
    int tl, int tr, int v) {
    if (r <= tl || tr <= l) return l - 1;
    if (l <= tl && tr <= r)
      return f(tree[v], tl, tr)
        ? find_last_in_subtree(f, tl, tr, v)
        : l - 1;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    int res =
      find_last_in_range(l, r, f, tm, tr, 2 * v + 1);
    if (res >= l) return res;
    return find_last_in_range(l, r, f, tl, tm, 2 * v);
  }
};
