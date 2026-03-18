//! https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
//! https://codeforces.com/blog/entry/118682
//! @code
//!   tree st1(n, 0, [&](int vl, int vr) {
//!     return vl + vr;
//!   });
//!   tree st(n, LLONG_MAX, ranges::min);
//!   st.max_right(l, r, [&](int m, ll value) {
//!     // value = op(a[l], a[l+1], ..., a[m-1])
//!     return value <= x;
//!   });
//!   st.min_left(l, r, [&](int m, ll value) {
//!     // value = op(a[m], ..., a[r-2], a[r-1])
//!     return value <= x;
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
  void max_right(int l, int r, const auto& f) {
    for (T x = unit; l < r;) {
      int u = l + n, v = __lg(min(u & -u, r - l)),
          m = l + (1 << v);
      if (T y = op(x, s[u >> v]); f(m, y)) l = m, x = y;
      else r = m - 1;
    }
  }
  void min_left(int l, int r, const auto& f) {
    for (T x = unit; l < r;) {
      int u = r + n, v = __lg(min(u & -u, r - l)),
          m = r - (1 << v);
      if (T y = op(s[(u - 1) >> v], x); f(m, y))
        r = m, x = y;
      else l = m + 1;
    }
  }
};
