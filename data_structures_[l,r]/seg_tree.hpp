//! https://codeforces.com/blog/entry/118682
//! @code
//!   tree st1(a, [&](int vl, int vr) {
//!     return vl + vr;
//!   });
//!   tree st(n, LLONG_MAX, ranges::min);
//!   st.max_right(l, r, [&](int m, ll value) -> bool {
//!     // l <= m <= r
//!     // value = op(a[l], a[l+1], ..., a[m])
//!   });
//!   st.min_left(l, r, [&](int m, ll value) -> bool {
//!     // l <= m <= r
//!     // value = op(a[m], ..., a[r-1], a[r])
//!   });
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
int nxt(int& l, int r) {
  int u = l, v = __lg(min(l & -l, r - l + 1));
  return l += 1 << v, u >> v;
}
template<class T, class F> struct tree {
  int n;
  F op;
  vector<T> s;
  tree(int n, T unit, F op): n(n), op(op), s(2 * n, unit) {}
  tree(const vector<T>& a, F op): n(ssize(a)), op(op), s(2 * n) {
    for (int i = 0; i < n; i++) s[i + n] = a[i];
    for (int i = n - 1; i >= 1; i--) s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;) s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) {
    T x = s[nxt(l += n, r += n)];
    while (l <= r) x = op(x, s[nxt(l, r)]);
    return x;
  }
  void max_right(int l, int r, auto f) {
    if (T x = s[l + n]; f(l, x))
      for (l++; l <= r;) {
        int u = l + n, v = __lg(min(u & -u, r - l + 1)), m = l + (1 << v) - 1;
        if (T y = op(x, s[u >> v]); f(m, y)) l = m + 1, x = y;
        else r = m - 1;
      }
  }
  int min_left(int l, int r, auto f) {
    if (T x = s[r + n]; f(r, x))
      for (r--; l <= r;) {
        int u = r + 1 + n, v = __lg(min(u & -u, r - l + 1)), m = r - (1 << v) + 1;
        if (T y = op(s[(u - 1) >> v], x); f(m, y)) r = m - 1, x = y;
        else l = m + 1;
      }
    return r;
  }
};
