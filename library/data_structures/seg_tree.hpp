#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
//! @code
//!   tree st0(n, INT_MAX, ranges::min); // -std=c++20
//!   tree st(n, INT_MAX, [&](int x, int y) -> int {
//!     return min(x, y);
//!   });
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T, class F> struct tree {
  int n;
  T unit;
  F f;
  vector<T> s;
  tree(int a_n, T a_unit, F a_f):
    n(a_n), unit(a_unit), f(a_f), s(2 * n, unit) {}
#include "seg_tree_uncommon/tree_vector_constructor.hpp"
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = f(s[2 * i], s[2 * i + 1]);
  }
  T query(int le, int ri) { // [le, ri)
    T x = unit, y = unit;
    for (le += n, ri += n; le < ri; le /= 2, ri /= 2) {
      if (le % 2) x = f(x, s[le++]);
      if (ri % 2) y = f(s[--ri], y);
    }
    return f(x, y);
  }
};
