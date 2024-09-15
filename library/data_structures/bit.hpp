//! @file
#pragma once
//! Binary Indexed Tree
// NOLINTNEXTLINE(readability-identifier-naming)
template <class T> struct BIT {
  vector<T> s;
  //! @param n initial size
  //! @time O(n)
  //! @space O(n) for `s` vector
  BIT(int n) : s(n) {}
#include "bit_uncommon/vector_constructor.hpp"
  //! @param i index
  //! @param d delta
  //! @time O(log n)
  //! @space O(1)
  void update(int i, T d) {
    for (; i < sz(s); i |= i + 1) s[i] += d;
  }
  //! @param ri defines range [0, ri)
  //! @returns a[0] + a[1] + ... + a[ri - 1]
  //! @time O(log n)
  //! @space O(1)
  T query(int ri) {
    T ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  //! @param le,ri defines range [le, ri)
  //! @returns a[le] + a[le + 1] + ... + a[ri - 1]
  //! @time O(log n)
  //! @space O(1)
  T query(int le, int ri) {
    return query(ri) - query(le);
  }
#include "bit_uncommon/lower_bound.hpp"
};
