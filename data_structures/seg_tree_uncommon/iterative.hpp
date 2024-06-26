/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the segment tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
inline int64_t op(int64_t vl, int64_t vr) { return vl + vr; }
/**
 * root is at tree[1]
 * internal nodes are [1, n)
 * leaf nodes are [n, 2 * n), but rotated such that a[0] is at tree[pw2]
 *     where pw2 is the only power of 2 such that n <= pw2 < 2 * n
 */
struct seg_tree {
  int n;
  vector<int64_t> tree, lazy;
  seg_tree(int a_n) : n(a_n), tree(2 * n), lazy(n) {}
  seg_tree(const vector<int>& a) : n((int)size(a)), tree(2 * n), lazy(n) {
    int pw2 = 1;
    while (pw2 < n) pw2 *= 2;
    for (int i = 0; i < (n); i++) tree[(i + pw2) % n + n] = a[i];
    for (int i = n - 1; i >= 1; i--) tree[i] = op(tree[2 * i], tree[2 * i + 1]);
  }
  inline void apply(int64_t change, int tl, int tr, int u) {
    tree[u] += (tr - tl) * change;
    if (u < n) lazy[u] += change;
  }
  inline void push(int tl, int tm, int tr, int u) {
    if (lazy[u]) {
      apply(lazy[u], tl, tm, 2 * u);
      apply(lazy[u], tm, tr, 2 * u + 1);
      lazy[u] = 0;
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  void update(int le, int ri, int64_t change) { update_impl(le, ri, change, 0, n, 1); }
  void update_impl(int le, int ri, int64_t change, int tl, int tr, int u) {
    if (ri <= tl || tr <= le) return;
    if (le <= tl && tr <= ri) return apply(change, tl, tr, u);
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    update_impl(le, ri, change, tl, tm, 2 * u);
    update_impl(le, ri, change, tm, tr, 2 * u + 1);
    tree[u] = op(tree[2 * u], tree[2 * u + 1]);
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  int64_t query(int le, int ri) { return query_impl(le, ri, 0, n, 1); }
  int64_t query_impl(int le, int ri, int tl, int tr, int u) {
    if (ri <= tl || tr <= le) return 0;
    if (le <= tl && tr <= ri) return tree[u];
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    return op(query_impl(le, ri, tl, tm, 2 * u),
              query_impl(le, ri, tm, tr, 2 * u + 1));
  }
  /**
   * @code{.cpp}
         st.find_first(le, ri, [&](ll x, int tl, int tr) -> bool {
         });
   * @endcode
   * @param le,ri defines range [le, ri)
   * @param f defines a function that returns true if the subtree contains an
   * element that satisfies the condition
   *
   * guarantee: `f` is called in order on the subtrees (tls are weakly
   * increasing) and at most once on each subtree
   *
   * if `f` returns true then every subsequent call to `f` will be a subtree of
   * the previous call; otherwise the next call will be a subsequent range of the
   * previous range
   *
   * @see seg_tree_find.test.cpp for more details
   *
   * @returns the index of the first element in the range that satisfies the
   * condition described in `f`, if no such element exists then `ri` is returned
   * @time O(log(n))
   * @space O(log(n)) for recursion stack
   */
  template <class F>
  int find_first(int le, int ri, const F& f) {
    return find_first_in_range(le, ri, f, 0, n, 1);
  }
  /**
   * invariant: f(tree[u], tl, tr) is true
   */
  template <class F>
  int find_first_in_subtree(const F& f, int tl, int tr, int u) {
    if (u >= n) return tl;
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    if (f(tree[2 * u], tl, tm)) return find_first_in_subtree(f, tl, tm, 2 * u);
    return find_first_in_subtree(f, tm, tr, 2 * u + 1);
  }
  template <class F>
  int find_first_in_range(int le, int ri, const F& f, int tl, int tr, int u) {
    if (ri <= tl || tr <= le) return ri;
    if (le <= tl && tr <= ri)
      return f(tree[u], tl, tr) ? find_first_in_subtree(f, tl, tr, u) : ri;
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    int res = find_first_in_range(le, ri, f, tl, tm, 2 * u);
    if (res < ri) return res;
    return find_first_in_range(le, ri, f, tm, tr, 2 * u + 1);
  }
  /**
   * @code{.cpp}
         st.find_last(le, ri, [&](ll x, int tl, int tr) -> bool {
         });
   * @endcode
   * @param le,ri defines range [le, ri)
   * @param f defines a function that returns true if the subtree contains an
   * element that satisfies the condition
   *
   * guarantee: `f` is called in order on the subtrees (trs are weakly
   * decreasing) and at most once on each subtree
   *
   * if `f` returns true then every subsequent call to `f` will be a subtree of
   * the previous call; otherwise the next call will be a subsequent range of the
   * previous range
   *
   * @see seg_tree_find.test.cpp for more details
   *
   * @returns the index of the last element in the range that satisfies the
   * condition described in `f`, if no such element exists then (le - 1) is
   * returned
   * @time O(log(n))
   * @space O(log(n)) for recursion stack
   */
  template <class F>
  int find_last(int le, int ri, const F& f) {
    return find_last_in_range(le, ri, f, 0, n, 1);
  }
  /**
   * invariant: f(tree[u], tl, tr) is true
   */
  template <class F>
  int find_last_in_subtree(const F& f, int tl, int tr, int u) {
    if (u >= n) return tl;
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    if (f(tree[2 * u + 1], tm, tr))
      return find_last_in_subtree(f, tm, tr, 2 * u + 1);
    return find_last_in_subtree(f, tl, tm, 2 * u);
  }
  template <class F>
  int find_last_in_range(int le, int ri, const F& f, int tl, int tr, int u) {
    if (ri <= tl || tr <= le) return le - 1;
    if (le <= tl && tr <= ri)
      return f(tree[u], tl, tr) ? find_last_in_subtree(f, tl, tr, u) : le - 1;
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    int res = find_last_in_range(le, ri, f, tm, tr, 2 * u + 1);
    if (res >= le) return res;
    return find_last_in_range(le, ri, f, tl, tm, 2 * u);
  }
};
/**
 * @see https://codeforces.com/blog/entry/18051
 *
 * Iterative query and update functions access the exact same set of indexes as
 * their recursive counterparts.
 */
struct iter_seg_tree {
  seg_tree st;
  int pw2;
  iter_seg_tree(seg_tree& a_st) : st(a_st), pw2(st.n ? 1 << __lg(2 * st.n - 1) : 0) {}
  inline void pull(int u) { st.tree[u] = op(st.tree[2 * u], st.tree[2 * u + 1]); }
  /**
   * @see https://github.com/ecnerwala/cp-book /blob/master/src/seg_tree.hpp
   */
  inline int to_leaf(int i) {
    i += pw2;
    return i < 2 * st.n ? i : 2 * (i - st.n);
  }
  /**
   * @see https://github.com/ecnerwala/cp-book /blob/master/src/seg_tree.hpp
   */
  inline pair<int, int> get_node_bounds(int a) {
    assert(1 <= a && a < 2 * st.n);
    int l = __builtin_clz(a) - __builtin_clz(2 * st.n - 1);
    int x = a << l, y = (a + 1) << l;
    assert(pw2 <= x && x < y && y <= 2 * pw2);
    return {(x >= 2 * st.n ? (x >> 1) + st.n : x) - pw2, (y >= 2 * st.n ? (y >> 1) + st.n : y) - pw2};
  }
  void push_parents(int le, int ri) {
    int lca_l_r = __lg((le - 1) ^ ri);
    for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) {
      auto [tl, tr] = get_node_bounds(le >> lg);
      st.push(tl, split(tl, tr), tr, le >> lg);
    }
    for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) {
      auto [tl, tr] = get_node_bounds(ri >> lg);
      st.push(tl, split(tl, tr), tr, ri >> lg);
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  void update_iter(int le, int ri, int64_t change) {
    assert(0 <= le && le <= ri && ri <= st.n);
    if (le == ri) return;
    le = to_leaf(le), ri = to_leaf(ri);
    push_parents(le, ri);
    for (int x = le, y = ri; x < y; x >>= 1, y >>= 1) {
      if (x & 1) {
        auto [tl, tr] = get_node_bounds(x);
        st.apply(change, tl, tr, x++);
      }
      if (y & 1) {
        auto [tl, tr] = get_node_bounds(--y);
        st.apply(change, tl, tr, y);
      }
    }
    int lca_l_r = __lg((le - 1) ^ ri);
    for (int lg = __builtin_ctz(ri) + 1; lg < (lca_l_r + 1); lg++) pull(ri >> lg);
    for (int lg = __builtin_ctz(le) + 1; lg < (__lg(le) + 1); lg++) pull(le >> lg);
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  int64_t query_iter(int le, int ri) {
    assert(0 <= le && le <= ri && ri <= st.n);
    if (le == ri) return 0;
    le = to_leaf(le), ri = to_leaf(ri);
    push_parents(le, ri);
    int64_t resl = 0, resr = 0;
    for (; le < ri; le >>= 1, ri >>= 1) {
      if (le & 1) resl = op(resl, st.tree[le++]);
      if (ri & 1) resr = op(st.tree[--ri], resr);
    }
    return op(resl, resr);
  }
};
