/** @file */
#pragma once
#include "persistent.hpp"
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html# preserving-the-history-of-its-values-persistent-segment-tree
 */
struct distinct_query {
  int n;
  PST pst;
  /**
   * @param a static array; can't handle updates
   * @time O(n log n)
   * @space O(n log n) for PST::tree vector
   */
  distinct_query(const vi& a) : n(sz(a)), pst(0, n + 1) {
    map<int, int> last_idx;
    rep (i, 0, n) {
      int& idx = last_idx[a[i]];
      pst.update(idx, 1, i);
      idx = i + 1;
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns number of distinct elements in range; query(i, i) returns 0.
   * @time O(log n)
   * @space O(log n) for recursion stack; no new nodes are allocated
   */
  inline int query(int le, int ri) {
    assert(0 <= le && le <= ri && ri <= n);
    return pst.query(0, le + 1, ri) - pst.query(0, le + 1, le);
  }
};
