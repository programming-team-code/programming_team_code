#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
//! @code
//!   tree st1(n, INT_MAX, ranges::min);
//!   tree st2(n, INT_MAX, [&](int x, int y) -> int {
//!     return min(x, y);
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
#include "seg_tree_uncommon/init.hpp"
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
};
