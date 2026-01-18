#pragma once
#include "../bit.hpp"
struct bit_rupq {
  int n;
  BIT bit = {0};
  bit_rupq(int n): n(n), bit(n) {}
  bit_rupq(vector<ll> a): n(sz(a)) {
    adjacent_difference(all(a), begin(a));
    bit = {a};
  }
  //! does a[l]+=d, a[l+1]+=d, .., a[r-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int l, int r, ll d) {
    if (l < n) bit.update(l, d);
    if (r < n) bit.update(r, -d);
  }
  //! @returns a[i]
  //! @time O(log n)
  //! @space O(1)
  ll get_index(int i) { return bit.query(i + 1); }
};
