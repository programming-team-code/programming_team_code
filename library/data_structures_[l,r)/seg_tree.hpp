#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
//! https://codeforces.com/blog/entry/118682
//! @code
//!   tree st1(n, 0, [&](int vl, int vr) {
//!     return vl + vr;
//!   });
//!   tree st(n, LLONG_MAX, ranges::min);
//!   st.max_right(l, r, [&](int m, ll value) {
//!     // l < m <= r
//!     // value = op(a[l], a[l+1], ..., a[m-1])
//!   });
//!   st.min_left(l, r, [&](int m, ll value) {
//!     // l <= m < r
//!     // value = op(a[m], ..., a[r-2], a[r-1])
//!   });
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T, class F> struct tree {
  int n;
  T unit;
  F op;
  vector<T> s;
  tree(int n, T unit, F op):
    n(n), unit(unit), op(op), s(2 * n, unit) {}
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) {
    T x = unit, y = unit;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l % 2) x = op(x, s[l++]);
      if (r % 2) y = op(s[--r], y);
    }
    return op(x, y);
  }
#include "seg_tree_uncommon/max_right.hpp"
#include "seg_tree_uncommon/min_left.hpp"
};
