#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
//! @code
//!   tree_inc st(n, INT_MAX, [&](int x, int y) -> int {
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
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) { // [b, e]
    T ra = unit, rb = unit;
    for (b += n, e += n; b <= e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2 == 0) rb = f(s[e--], rb);
    }
    return f(ra, rb);
  }
};
