#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
//! @code
//!   tree_inc st3(a, ranges::min);
//!   tree_inc st4(a, [&](int x, int y) -> int {
//!     return min(x, y);
//!   });
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T, class F> struct tree_inc {
  int n;
  F f;
  vector<T> s;
  tree_inc(const vector<T>& a, F f):
    n(sz(a)), f(f), s(2 * n) {
    rep(i, 0, n) s[i + n] = a[i];
    for (int i = n - 1; i > 0; i--)
      s[i] = f(s[2 * i], s[2 * i + 1]);
  }
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = f(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) { // [l, r]
    optional<T> x, y;
    for (l += n, r += n; l <= r; ++l /= 2, --r /= 2) {
      if (l % 2 == 1) x = x ? f(*x, s[l]) : s[l];
      if (r % 2 == 0) y = y ? f(s[r], *y) : s[r];
    }
    return x ? (y ? f(*x, *y) : *x) : *y;
  }
};
