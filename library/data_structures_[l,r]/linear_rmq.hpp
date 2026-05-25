#pragma once
//! https://codeforces.com/blog/entry/153134
//! https://codeforces.com/blog/entry/125371?#comment-1173604
//! @code
//!   linear_rmq rmq1(a, less());          //right-most min
//!   linear_rmq rmq2(a, less_equal());    //left-most min
//!   linear_rmq rmq3(a, greater());       //right-most max
//!   linear_rmq rmq4(a, greater_equal()); //left-most max
//!   linear_rmq rmq5(a, [&](auto& x, auto& y) {
//!     return x < y;
//!   });
//! @endcode
//! @time O(n + q)
//! @space O(n)
template<class T, class F> struct linear_rmq {
  int n;
  vector<T> a;
  F cmp;
  vi in, asc, head;
  linear_rmq(const vector<T>& a, F cmp):
    n(sz(a)), a(a), cmp(cmp), in(n), asc(n), head(n + 1) {
    vi st(n + 1, -1);
    for (int i = 0, t = 0; i <= n; i++) {
      int prev = 0;
      while (t && (i == n || !cmp(a[st[t]], a[i]))) {
        head[prev] = st[t];
        auto j = st[t - 1] + 1u, k = bit_floor(i ^ j);
        in[st[t--]] = prev = i & -k, asc[j] |= k;
      }
      st[++t] = head[prev] = i;
    }
    rep(i, 1, n)
      asc[i] = (asc[i] | asc[i - 1]) & -(in[i] & -in[i]);
  }
  int idx(int l, int r) {
    if (unsigned j = in[l] ^ in[r]) {
      j = asc[l] & asc[r] & -bit_floor(j);
      if (int k = bit_floor(asc[l] ^ j))
        l = head[(in[l] & -k) | k];
      if (int k = bit_floor(asc[r] ^ j))
        r = head[(in[r] & -k) | k];
    }
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[idx(l, r)]; }
};
