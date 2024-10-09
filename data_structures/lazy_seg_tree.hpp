//! https://codeforces.com/blog/entry/112755
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
int64_t op(int64_t vl, int64_t vr) { return vl + vr; }
struct seg_tree {
  int n;
  vector<int64_t> tree, lazy;
  seg_tree(int a_n): n(a_n), tree(2 * n), lazy(n) {}
  seg_tree(const vector<int>& a):
    n((int)size(a)), tree(2 * n), lazy(n) {
    int pw2 = 1;
    while (pw2 < n) pw2 *= 2;
    for (int i = 0; i < (n); i++)
      tree[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--)
      tree[i] = op(tree[2 * i], tree[2 * i + 1]);
  }
  void apply(int64_t change, int tl, int tr, int v) {
    tree[v] += (tr - tl) * change;
    if (v < n) lazy[v] += change;
  }
  void push(int tl, int tm, int tr, int v) {
    if (lazy[v]) {
      apply(lazy[v], tl, tm, 2 * v);
      apply(lazy[v], tm, tr, 2 * v + 1);
      lazy[v] = 0;
    }
  }
  void update(int le, int ri, int64_t change) { // [le, ri)
    update_impl(le, ri, change, 0, n, 1);
  }
  void update_impl(int le, int ri, int64_t change, int tl,
    int tr, int v) {
    if (ri <= tl || tr <= le) return;
    if (le <= tl && tr <= ri)
      return apply(change, tl, tr, v);
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    update_impl(le, ri, change, tl, tm, 2 * v);
    update_impl(le, ri, change, tm, tr, 2 * v + 1);
    tree[v] = op(tree[2 * v], tree[2 * v + 1]);
  }
  int64_t query(int le, int ri) { // [le, ri)
    return query_impl(le, ri, 0, n, 1);
  }
  int64_t query_impl(int le, int ri, int tl, int tr,
    int v) {
    if (ri <= tl || tr <= le) return 0;
    if (le <= tl && tr <= ri) return tree[v];
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    return op(query_impl(le, ri, tl, tm, 2 * v),
      query_impl(le, ri, tm, tr, 2 * v + 1));
  }
  //! @code
  //!   seg_tree st1(n);
  //!   st1.find_first(le, ri, [&](ll x, int tl, int tr) ->
  //!   bool {
  //!   });
  //! @endcode
  //! @param le,ri defines range [le, ri)
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
  //! such element exists then `ri` is returned
  //! @time O(log(n))
  //! @space O(log(n)) for recursion stack
  template<class F>
  int find_first(int le, int ri, const F& f) {
    return find_first_in_range(le, ri, f, 0, n, 1);
  }
  //! invariant: f(tree[v], tl, tr) is 1
  template<class F>
  int find_first_in_subtree(const F& f, int tl, int tr,
    int v) {
    if (v >= n) return tl;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    if (f(tree[2 * v], tl, tm))
      return find_first_in_subtree(f, tl, tm, 2 * v);
    return find_first_in_subtree(f, tm, tr, 2 * v + 1);
  }
  template<class F>
  int find_first_in_range(int le, int ri, const F& f,
    int tl, int tr, int v) {
    if (ri <= tl || tr <= le) return ri;
    if (le <= tl && tr <= ri)
      return f(tree[v], tl, tr)
        ? find_first_in_subtree(f, tl, tr, v)
        : ri;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    int res =
      find_first_in_range(le, ri, f, tl, tm, 2 * v);
    if (res < ri) return res;
    return find_first_in_range(le, ri, f, tm, tr,
      2 * v + 1);
  }
  //! @code
  //!   seg_tree st2(n);
  //!   st2.find_last(le, ri, [&](ll x, int tl, int tr) ->
  //!   bool {
  //!   });
  //! @endcode
  //! @param le,ri defines range [le, ri)
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
  //! such element exists then (le - 1) is returned
  //! @time O(log(n))
  //! @space O(log(n)) for recursion stack
  template<class F>
  int find_last(int le, int ri, const F& f) {
    return find_last_in_range(le, ri, f, 0, n, 1);
  }
  //! invariant: f(tree[v], tl, tr) is 1
  template<class F>
  int find_last_in_subtree(const F& f, int tl, int tr,
    int v) {
    if (v >= n) return tl;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    if (f(tree[2 * v + 1], tm, tr))
      return find_last_in_subtree(f, tm, tr, 2 * v + 1);
    return find_last_in_subtree(f, tl, tm, 2 * v);
  }
  template<class F>
  int find_last_in_range(int le, int ri, const F& f,
    int tl, int tr, int v) {
    if (ri <= tl || tr <= le) return le - 1;
    if (le <= tl && tr <= ri)
      return f(tree[v], tl, tr)
        ? find_last_in_subtree(f, tl, tr, v)
        : le - 1;
    int tm = split(tl, tr);
    push(tl, tm, tr, v);
    int res =
      find_last_in_range(le, ri, f, tm, tr, 2 * v + 1);
    if (res >= le) return res;
    return find_last_in_range(le, ri, f, tl, tm, 2 * v);
  }
};
