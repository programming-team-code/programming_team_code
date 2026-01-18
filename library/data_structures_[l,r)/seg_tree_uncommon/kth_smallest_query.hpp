#pragma once
#include "persistent.hpp"
//! https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
struct kth_smallest {
  PST pst;
  //! @param a,minv,maxv must satisfy: minv <= a[i] < maxv
  //! @time O(n log(maxv - minv))
  //! @space O(n log(maxv - minv)) nodes are pushed back
  //! onto PST::tree
  kth_smallest(const vi& a, int minv, int maxv):
    pst(minv, maxv) {
    rep(i, 0, sz(a)) pst.update(a[i], 1, i);
  }
  //! @param l,r defines range [l, r)
  //! @param k must satisfy 1 <= k <= r - l
  //! @returns kth smallest number in range.
  //!     - query(l,r,1) returns the min
  //!     - query(l,r,(r-l)) returns the max
  //! @time O(log(maxv - minv))
  //! @space O(log(maxv - minv)) for recursion stack; no
  //! new nodes are allocated
  int query(int l, int r, int k) {
    return query(k, pst.root_l, pst.root_r,
      pst.roots[l], pst.roots[r]);
  }
  int query(int k, int tl, int tr, int vl, int vr) {
    if (tr - tl == 1) return tl;
    int tm = tl + (tr - tl) / 2;
    int left_count = pst.tree[pst.tree[vr].lch].sum -
      pst.tree[pst.tree[vl].lch].sum;
    if (left_count >= k)
      return query(k, tl, tm, pst.tree[vl].lch,
        pst.tree[vr].lch);
    return query(k - left_count, tm, tr,
      pst.tree[vl].rch, pst.tree[vr].rch);
  }
};
