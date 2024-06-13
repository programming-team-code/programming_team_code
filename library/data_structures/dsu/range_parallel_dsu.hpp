/** @file */
#pragma once
/**
 * DSU with support for joining two parallel ranges [l1, l1 + len) and [l2, l2 +
 * len) such that edges of the form (l1 + i, l2 + i) are joined. for all `i` in
 * [0, len). The complexity of a single query is O(n), but the total complexity
 * across all queries is O(n log n), so O(log n) amortized per query.
 *
 * @time O(n log n) amortized across all queries
 * @space O(n log n)
 */
struct range_parallel_dsu {
#include "../../../kactl/content/data-structures/UnionFind.h"
  vector<UF> ufs;
  /*
   * constructs a range_parallel_dsu with n elements.
   */
  range_parallel_dsu(int n) : ufs(__lg(n) + 1, UF(n)) {}
  /*
   * joins the ranges [l1, l1 + len) and [l2, l2 + len) such that edges of the
   * form (l1 + i, l2 + i) are joined. for all `i` in [0, len). The function `f`
   * is called for each connected component of the resulting graph, with the
   * first argument being the representative of the component and the second
   * argument being the parent of the component which is being joined.
   *
   * @time O(log n) amortized
   * @space O(log n) due to the recursive stack
   */
  template <typename F>
  void join(int l1, int l2, int len, const F& f) {
    if (len == 0) return;
    int lg = __lg(len);
    join_impl(lg, l1, l2, f);
    join_impl(lg, l1 + len - (1 << lg), l2 + len - (1 << lg), f);
  }
  template <typename F>
  void join_impl(int lvl, int u, int v, const F& f) {
    if (lvl == 0) {
      int a = ufs[lvl].find(u), b = ufs[lvl].find(v);
      if (a == b) return;
      ufs[0].join(a, b);
      int c = ufs[0].find(a);
      return f(c, a ^ b ^ c);
    }
    if (!ufs[lvl].join(u, v)) return;
    join_impl(lvl - 1, u, v, f);
    join_impl(lvl - 1, u + (1 << (lvl - 1)), v + (1 << (lvl - 1)), f);
  }
};
