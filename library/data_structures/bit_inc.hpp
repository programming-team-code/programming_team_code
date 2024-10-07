#pragma once
//! @code
//!   bit_inc<int> bit3(n);
//!   bit_inc<ll> bit4(n);
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T> struct bit_inc {
  vector<T> s;
  bit_inc(int n): s(n) {}
  void update(int i, T d) {
    for (; i < sz(s); i |= i + 1) s[i] += d;
  }
  T query(int i) { // [0, i]
    T ret = 0;
    for (; i >= 0; (i &= i + 1)--) ret += s[i];
    return ret;
  }
  T query(int le, int ri) { // [le, ri]
    return query(ri) - query(le - 1);
  }
};
