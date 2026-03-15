#pragma once
//! https://codeforces.com/blog/entry/118682
//! @code
//!   tree st1(n, 0, [&](int vl, int vr) {
//!     return vl + vr;
//!   });
//!   tree st(a, ranges::min);
//!   st.max_right(l, r, [&](int m, int value) {
//!     // value = op(a[l], a[l+1], ..., a[m])
//!     return value <= x;
//!   });
//!   st.min_left(l, r, [&](int m, int value) {
//!     // value = op(a[m], ..., a[r-1], a[r])
//!     return value <= x;
//!   });
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
