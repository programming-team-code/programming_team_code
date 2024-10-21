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
  tree(const vector<T>& a, T a_unit, F a_f):
    n(ssize(a)), unit(a_unit), f(a_f), s(2 * n) {
    for (int i = 0; i < n; i++) s[i + n] = a[i];
    for (int i = n - 1; i > 0; i--)
      s[i] = f(s[2 * i], s[2 * i + 1]);
  }
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = f(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) { // [l, r)
    T x = unit, y = unit;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l % 2) x = f(x, s[l++]);
      if (r % 2) y = f(s[--r], y);
    }
    return f(x, y);
  }
};
