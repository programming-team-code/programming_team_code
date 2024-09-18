#pragma once
// NOLINTNEXTLINE(readability-identifier-naming)
//! @code
//!   bit.query(ri); // sum of [0, ri)
//!   bit.query(le, ri); // sum of [le, ri)
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T> struct BIT {
  vector<T> s;
  BIT(int n): s(n) {}
#include "bit_uncommon/vector_constructor.hpp"
  void update(int i, T d) {
    for (; i < sz(s); i |= i + 1) s[i] += d;
  }
  T query(int ri) {
    T ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  T query(int le, int ri) { return query(ri) - query(le); }
#include "bit_uncommon/lower_bound.hpp"
};
