#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
//! @code
//!   tree_inc st3(n, INT_MAX, ranges::min); // -std=c++20
//!   tree_inc st4(n, INT_MAX, [&](int x, int y) -> int {
//!     return min(x, y);
//!   });
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T, class F> struct tree_inc {
  int n;
  T unit;
  F f;
  vector<T> s;
  tree_inc(int a_n, T a_unit, F a_f):
    n(a_n), unit(a_unit), f(a_f), s(2 * n, unit) {}
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = f(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) { // [l, r]
    T x = unit, y = unit;
    for (l += n, r += n; l <= r; l /= 2, r /= 2) {
      if (l % 2 == 1) x = f(x, s[l++]);
      if (r % 2 == 0) y = f(s[r--], y);
    }
    return f(x, y);
  }
};
