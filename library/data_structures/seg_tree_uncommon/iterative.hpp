/** @file */
#pragma once
#include "../seg_tree.hpp"
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
  inline array<int, 2> get_node_bounds(int a) {
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
  void update_iter(int le, int ri, ll change) {
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
    for (int lg = __builtin_ctz(ri) + 1; lg <= lca_l_r; lg++) pull(ri >> lg);
    for (int lg = __builtin_ctz(le) + 1; lg <= __lg(le); lg++) pull(le >> lg);
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  ll query_iter(int le, int ri) {
    assert(0 <= le && le <= ri && ri <= st.n);
    if (le == ri) return 0;
    le = to_leaf(le), ri = to_leaf(ri);
    push_parents(le, ri);
    auto resl = 0LL, resr = 0LL;
    for (; le < ri; le >>= 1, ri >>= 1) {
      if (le & 1) resl = op(resl, st.tree[le++]);
      if (ri & 1) resr = op(st.tree[--ri], resr);
    }
    return op(resl, resr);
  }
};
