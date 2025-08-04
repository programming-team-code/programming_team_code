#pragma once
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
  vi asc, in, head;
  linear_rmq(const vector<T>& a, F cmp):
    n(sz(a)), a(a), cmp(cmp), asc(n), in(n), head(n + 1) {
    vi st{-1};
    rep(i, 0, n + 1) {
      int prev = 0;
      while (sz(st) > 1 &&
        (i == n || !cmp(a[st.back()], a[i]))) {
        head[prev] = st.back();
        int b = bit_floor((end(st)[-2] + 1u) ^ i);
        in[st.back()] = prev = i & -b;
        st.pop_back();
        asc[st.back() + 1] |= b;
      }
      head[prev] = i;
      st.push_back(i);
    }
    rep(i, 1, n)(asc[i] |= asc[i - 1]) &=
      -(in[i] & -in[i]);
  }
  int idx(int l, int r) { // [l, r]
    if (unsigned j = in[l] ^ in[r]; j) {
      j = asc[l] & asc[r] & -bit_floor(j);
      if (unsigned k = asc[l] ^ j; k)
        k = bit_floor(k), l = head[(in[l] & -k) | k];
      if (unsigned k = asc[r] ^ j; k)
        k = bit_floor(k), r = head[(in[r] & -k) | k];
    }
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[idx(l, r)]; }
};
