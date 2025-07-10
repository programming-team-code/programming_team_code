#pragma once
#include "wavelet_bit_vec.hpp"
struct wavelet_matrix {
  int n;
  vector<bit_vec> bv;
  //! Requires a[i] <= max_val
  //! @time O(n * log(max_val))
  //! @space O(n * log(max_val) / 64)
  wavelet_matrix(vector<ull> a, ull max_val):
    n(sz(a)), bv(bit_width(max_val), {{}}) {
    for (int h = sz(bv); h--;) {
      int i = 0;
      vector<bool> b(n);
      ranges::stable_partition(a,
        [&](ull x) { return b[i++] = !((x >> h) & 1); });
      bv[h] = b;
    }
  }
  //! (k+1)th smallest number in [l,r)
  //! kth(l,r,0) returns the min
  //! @time O(log(max_val))
  //! @space O(1)
  ull kth(int l, int r, int k) {
    ll res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = bv[h].cnt(l), r0 = bv[h].cnt(r);
      if (k < r0 - l0) l = l0, r = r0;
      else
        k -= r0 - l0, res |= 1ULL << h,
          l += bv[h].cnt(n) - l0, r += bv[h].cnt(n) - r0;
    }
    return res;
  }
#include "wavelet_count_less.hpp"
};
