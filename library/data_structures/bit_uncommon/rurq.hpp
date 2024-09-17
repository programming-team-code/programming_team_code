//! @file
#pragma once
#include "../bit.hpp"
//! @see https://blog.mitrichev.ch/2013/05/fenwick-tree-range-updates.html
//! range update, range query
template <class T> struct bit_rurq {
  int n;
  BIT<T> bit1 = {0}, bit2 = {0};
  //! @param a_n size
  //! @time O(n)
  //! @space O(n) for both bits
  bit_rurq(int a_n) : n(a_n), bit1(n), bit2(n) {}
  //! @param a initial array
  //! @time O(n)
  //! @space O(n) for both bits
  bit_rurq(vector<T> a) : n(sz(a)) {
    adjacent_difference(all(a), begin(a));
    bit1 = {a};
    rep(i, 0, n) a[i] *= i;
    bit2 = {a};
  }
  //! does a[le] += d, a[le + 1] += d, ..., a[ri - 1] += d
  //!
  //! @param le,ri defines range [le, ri)
  //! @param d delta to add to each index in range
  //! @time O(log n)
  //! @space O(1)
  void update(int le, int ri, T d) {
    if (le < n) {
      bit1.update(le, d);
      bit2.update(le, d * le);
    }
    if (ri < n) {
      bit1.update(ri, -d);
      bit2.update(ri, -d * ri);
    }
  }
  //! @param ri defines range [0, ri)
  //! @returns a[0] + a[1] + ... + a[ri - 1]
  //! @time O(log n)
  //! @space O(1)
  T query(int ri) {
    return bit1.query(ri) * ri - bit2.query(ri);
  }
  //! @param le,ri defines range [le, ri)
  //! @returns a[le] + a[le + 1] + ... + a[ri - 1]
  //! @time O(log n)
  //! @space O(1)
  T query(int le, int ri) {
    return query(ri) - query(le);
  }
};
