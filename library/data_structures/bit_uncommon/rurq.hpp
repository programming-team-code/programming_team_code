#pragma once
#include "../bit.hpp"
//! https://blog.mitrichev.ch/2013/05/fenwick-tree-range-updates.html
template<class T> struct bit_rurq {
  int n;
  BIT<T> bit1 = {0}, bit2 = {0};
  bit_rurq(int a_n): n(a_n), bit1(n), bit2(n) {}
  bit_rurq(vector<T> a): n(sz(a)) {
    adjacent_difference(all(a), begin(a));
    bit1 = {a};
    rep(i, 0, n) a[i] *= i;
    bit2 = {a};
  }
  //! does a[le]+=d, a[le+1]+=d, ..., a[ri-1]+=d
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
  //! @returns a[0]+a[1]+...+a[ri-1]
  //! @time O(log n)
  //! @space O(1)
  T query(int ri) {
    return bit1.query(ri) * ri - bit2.query(ri);
  }
  //! @returns a[le]+a[le+1]+...+a[ri-1]
  //! @time O(log n)
  //! @space O(1)
  T query(int le, int ri) { return query(ri) - query(le); }
};
