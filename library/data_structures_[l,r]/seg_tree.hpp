#pragma once
//! https://codeforces.com/blog/entry/118682
//! @code
//!   tree st1(n, 0, [&](int vl, int vr) {
//!     return vl + vr;
//!   });
//!   tree st(a, ranges::min);
//!   int idx = st.max_right(l, r, [&](int value) {
//!     return value <= x;
//!   });
//!   // idx in [l, r+1]
//!   // f(op(a[l], a[l+1], ..., a[idx-1])) is true
//!   // f(op(a[l], a[l+1], ..., a[idx])) is false
//!   idx = st.min_left(l, r, [&](int value) {
//!     return value <= x;
//!   });
//!   // idx in [l-1, r]
//!   // f(op(a[idx+1], ..., a[r-1], a[r])) is true
//!   // f(op(a[idx], ..., a[r-1], a[r])) is false
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
int nxt(int& l, int r) {
  int x = l, y = __lg(min(l & -l, r - l + 1));
  return l += 1 << y, x >> y;
}
template<class T, class F> struct tree {
  int n;
  F op;
  vector<T> s;
  tree(int n, T unit, F op):
    n(n), op(op), s(2 * n, unit) {}
#include "seg_tree_uncommon/init.hpp"
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) {
    T x = s[nxt(l += n, r += n)];
    while (l <= r) x = op(x, s[nxt(l, r)]);
    return x;
  }
#include "seg_tree_uncommon/max_right.hpp"
#include "seg_tree_uncommon/min_left.hpp"
};
