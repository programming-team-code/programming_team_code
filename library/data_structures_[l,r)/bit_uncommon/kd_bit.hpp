#pragma once
//! https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/data-structures/KDBIT.h
//! @code
//!   KD_BIT<2> bit(n, m);
//!   bit.update(i, j, 5);
//!   // 0 <= i < n
//!   // 0 <= j < m
//!   bit.query(i1, i2, j1, j2);
//!   // 0 <= i1 <= i2 <= n
//!   // 0 <= j1 <= j2 <= m
//! @endcode
//! @time O(n^k + q * log^k n)
//! @space O(n^k)
// NOLINTNEXTLINE(readability-identifier-naming)
template<int K> struct KD_BIT {
  vector<KD_BIT<K - 1>> s;
  template<class... A>
  KD_BIT(int n, A... a): s(n, KD_BIT<K - 1>(a...)) {}
  template<class... A> void update(int i, A... a) {
    for (; i < sz(s); i |= i + 1) s[i].update(a...);
  }
  template<class... A> ll query(int l, int r, A... a) {
    ll ans = 0;
    for (; l < r; r &= r - 1) ans += s[r - 1].query(a...);
    for (; r < l; l &= l - 1) ans -= s[l - 1].query(a...);
    return ans;
  }
};
template<> struct KD_BIT<0> {
  ll s = 0;
  void update(ll v) { s += v; }
  ll query() { return s; }
};
