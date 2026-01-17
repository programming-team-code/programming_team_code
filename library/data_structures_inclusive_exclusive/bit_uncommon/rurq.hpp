#pragma once
#include "../bit.hpp"
//! https://blog.mitrichev.ch/2013/05/fenwick-tree-range-updates.html
struct bit_rurq {
  int n;
  BIT bit1 = {0}, bit2 = {0};
  bit_rurq(int n): n(n), bit1(n), bit2(n) {}
  bit_rurq(vector<ll> a): n(sz(a)) {
    adjacent_difference(all(a), begin(a));
    bit1 = {a};
    rep(i, 0, n) a[i] *= i;
    bit2 = {a};
  }
  //! does a[l]+=d, a[l+1]+=d, ..., a[r-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int l, int r, ll d) {
    if (l < n) {
      bit1.update(l, d);
      bit2.update(l, d * l);
    }
    if (r < n) {
      bit1.update(r, -d);
      bit2.update(r, -d * r);
    }
  }
  //! @returns a[0]+a[1]+...+a[r-1]
  //! @time O(log n)
  //! @space O(1)
  ll query(int r) {
    return bit1.query(r) * r - bit2.query(r);
  }
  //! @returns a[l]+a[l+1]+...+a[r-1]
  //! @time O(log n)
  //! @space O(1)
  ll query(int l, int r) { return query(r) - query(l); }
};
