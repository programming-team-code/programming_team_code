#pragma once
//! https://codeforces.com/blog/entry/118682
//! @code
//!   {
//!     tree st(n, pii{}, [&](pii& l, pii& r) {
//!       return min(l, r);
//!     });
//!   }
//!   tree st(n, int{}, ranges::min);
//!   rep(i, 0, n) st.update(i, a[i]);
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
int nxt(int& l, int r) {
  int lg = __lg(min(l & -l, r - l + 1));
  return exchange(l, l + (1 << lg)) >> lg;
}
template<class T, class F> struct tree {
  int n;
  F op;
  vector<T> s;
  tree(int n, T, F op): n(n), op(op), s(2 * n) {}
  void update(int i, T val) {
    for (s[i += n] = val; i /= 2;)
      s[i] = op(s[2 * i], s[2 * i + 1]);
  }
  T query(int l, int r) {
    T res = s[nxt(l += n, r += n)];
    while (l <= r) res = op(res, s[nxt(l, r)]);
    return res;
  }
};
