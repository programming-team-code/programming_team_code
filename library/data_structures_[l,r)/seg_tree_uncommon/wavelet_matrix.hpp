#pragma once
#include "wavelet_bit_vec.hpp"
//! https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp
//! @code
//!   vector<ll> a(n);
//!   wavelet_matrix wm(a, 30); // 0 <= a[i] < (1LL<<30)
//!   wm.kth(l, r, k); //(k+1)th smallest number in [l,r)
//!   wm.kth(l, r, 0); //min in [l,r)
//! @endcode
//! @time O(n * lg + q * lg)
//! @space O(n * lg / 64)
struct wavelet_matrix {
  int n;
  vector<bit_vec> bv;
  wavelet_matrix(vector<ll> a, int lg):
    n(sz(a)), bv(lg, {{}}) {
    for (int h = sz(bv); h--;) {
      vector<bool> b(n);
      rep(i, 0, n) b[i] = (~a[i] >> h) & 1;
      bv[h] = b;
      ranges::stable_partition(a,
        [&](ll x) { return (~x >> h) & 1; });
    }
  }
  ll kth(int l, int r, int k) {
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
