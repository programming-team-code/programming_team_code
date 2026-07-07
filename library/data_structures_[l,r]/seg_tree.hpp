#pragma once
//! https://codeforces.com/blog/entry/118682
//! @code
//!   tree st1(a, [&](int vl, int vr) {
//!     return vl + vr;
//!   });
//!   tree st(n, LLONG_MAX, ranges::min);
//!   int m1 = st.max_right(l, r,
//!     [&](int m, ll value) -> bool {
//!       // l <= m <= r
//!       // value = op(a[l], a[l+1], ..., a[m])
//!     }); // min m such that f fails; r+1 if none
//!   int m2 = st.min_left(l, r,
//!     [&](int m, ll value) -> bool {
//!       // l <= m <= r
//!       // value = op(a[m], ..., a[r-1], a[r])
//!     }); // max m such that f fails; l-1 if none
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
int nxt(int& l, int r) {
  int u = l,
      v = bit_width(min(l & -l, r - l + 1) + 0u) - 1;
  return l += 1 << v, u >> v;
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
