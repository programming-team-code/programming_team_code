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
  T query(int ri) { // [0, ri]
    T ret = 0;
    for (; ri >= 0; ri = (ri & (ri + 1)) - 1) ret += s[ri];
    return ret;
  }
  T query(int le, int ri) { // [le, ri]
    return query(ri) - query(le - 1);
  }
#include "bit_uncommon/lower_bound.hpp"
};
