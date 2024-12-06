#pragma once
//! https://codeforces.com/blog/entry/118682
//! @code
//!   tree_inc st3(a, ranges::min);
//!   tree_inc st4(a, [&](int x, int y) -> int {
//!     return min(x, y);
//!   });
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
int nxt(int& l, int r) {
  int lg = __lg(min(l & -l, r - l + 1));
  return exchange(l, l + (1 << lg)) >> lg;
}
template<class T, class F> struct tree_inc {
  int n;
  F op;
  vector<T> s;
  tree_inc(const vector<T>& a, F op):
    n(sz(a)), op(op), s(2 * n) {
    ranges::copy(a, begin(s) + n);
    for (int i = n - 1; i > 0; i--)
      s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) { // [l, r]
    T res = s[nxt(l += n, r += n)];
    while (l <= r) res = op(res, s[nxt(l, r)]);
    return res;
  }
};
