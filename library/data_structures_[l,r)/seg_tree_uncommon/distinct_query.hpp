#pragma once
#include "persistent.hpp"
//! https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
struct distinct_query {
  int n;
  PST pst;
  //! @param a static array; can't handle updates
  //! @time O(n log n)
  //! @space O(n log n)
  distinct_query(const vi& a): n(sz(a)), pst(0, n + 1) {
    map<int, int> last_idx;
    rep(i, 0, n) {
      int& idx = last_idx[a[i]];
      pst.update(idx, 1, i);
      idx = i + 1;
    }
  }
  //! @param l,r defines range [l, r)
  //! @returns number of distinct elements in range;
  //! query(i, i) returns 0.
  //! @time O(log n)
  //! @space O(log n)
  int query(int l, int r) {
    return pst.query(0, l + 1, r) - pst.query(0, l + 1, l);
  }
};
