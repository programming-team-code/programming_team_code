#pragma once
#include "wavelet_bit_vec.hpp"
//! https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp
//! @code
//!   vector<ll> a(n);
//!   wavelet_matrix wm(a, 30); // 0 <= a[i] < (1<<30)
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
      int x = bv[h].cnt(l), y = bv[h].cnt(r);
      if (k < y - x) l = x, r = y;
      else
        k -= y - x, res += 1LL << h, l += bv[h].cnt(n) - x,
          r += bv[h].cnt(n) - y;
    }
    return res;
  }
#include "wavelet_count_less.hpp"
};
