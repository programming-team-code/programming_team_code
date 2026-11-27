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
  vector<T> a;
  F cmp;
  vi asc, head;
  linear_rmq(const vector<T>& a, F cmp):
    a(a), cmp(cmp), asc(sz(a)), head(asc) {
    vi st({-1});
    rep(i, 0, sz(a)) {
      int prev = i;
      while (sz(st) > 1 && !cmp(a[st.back()], a[i])) {
        auto j = end(st)[-2] + 1u, k = bit_floor(i ^ j);
        head[prev = j | (k - 1)] = j - 1;
        asc[j] |= k, asc[st.back()] |= k;
        st.pop_back();
      }
      st.push_back(head[prev] = i);
    }
    rep(i, 1, sz(a)) asc[i] |= asc[i - 1] & -asc[i];
  }
  int idx(int l, int r) {
    auto j = asc[l] & asc[r] & -bit_floor((l ^ r) | 1u);
    if (int k = bit_floor(asc[l] ^ j))
      l = head[(l & ~k) | (k - 1)];
    if (int k = bit_floor(asc[r] ^ j))
      r = head[(r & ~k) | (k - 1)];
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[idx(l, r)]; }
};
