//! https://codeforces.com/blog/entry/118682
//! @code
//!   {
//!     tree st(a, [&](int vl, int vr) {
//!       return vl & vr;
//!     });
//!   }
//!   {
//!     tree st(n, 0LL, plus<ll>{});
//!   }
//!   {
//!     tree st(n, INT_MAX, ranges::min);
//!     int idx = st.walk(l, r, [&](int value) {
//!       return value <= x;
//!     }); // smallest index in [l, r] s.t. f is false
//!   }
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
  tree(const vector<T>& a, F op):
    n(ssize(a)), op(op), s(2 * n) {
    for (int i = 0; i < n; i++) s[i + n] = a[i];
    for (int i = n - 1; i >= 1; i--)
      s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) {
    T x = s[nxt(l += n, r += n)];
    while (l <= r) x = op(x, s[nxt(l, r)]);
    return x;
  }
  int walk(int l, int r, const auto& f) {
    if (T x = s[l + n]; f(x))
      for (l++; l <= r;) {
        int u = l + n, v = __lg(min(u & -u, r - l + 1));
        if (T y = op(x, s[u >> v]); f(y))
          l += 1 << v, x = y;
        else r = l + (1 << v) - 2;
      }
    return l;
  }
};
