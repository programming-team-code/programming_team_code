#pragma once
#include "../bit.hpp"
struct bit_rupq {
  int n;
  BIT bit = {0};
  bit_rupq(int a_n): n(a_n), bit(n) {}
  bit_rupq(vector<ll> a): n(sz(a)) {
    adjacent_difference(all(a), begin(a));
    bit = {a};
  }
  //! does a[le]+=d, a[le+1]+=d, .., a[ri-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int le, int ri, ll d) {
    if (le < n) bit.update(le, d);
    if (ri < n) bit.update(ri, -d);
  }
  //! @returns a[i]
  //! @time O(log n)
  //! @space O(1)
  ll get_index(int i) { return bit.query(i + 1); }
};
