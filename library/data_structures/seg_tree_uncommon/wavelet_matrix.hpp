#pragma once
#include "bit_vec.hpp"
struct wavelet_matrix {
  int n;
  vector<bit_vec> bv;
  //! Requires 0 <= a[i] < max_val
  wavelet_matrix(const vector<ll>& a, ll max_val):
    n(sz(a)), bv(bit_width(uint64_t(max_val)), {{}}) {
    vector<ll> cur(a), nxt(n);
    for (int h = sz(bv); h--;) {
      vector<bool> b(n);
      rep(i, 0, n) b[i] = (cur[i] >> h) & 1;
      bv[h] = b;
      array it{begin(nxt), begin(nxt) + bv[h].cnt0(n)};
      rep(i, 0, n) * it[b[i]]++ = cur[i];
      swap(cur, nxt);
    }
  }
  ll kth(int l, int r, int k) {
    ll res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if (k < r0 - l0) l = l0, r = r0;
      else
        k -= r0 - l0, res |= 1LL << h,
          l += bv[h].cnt0(n) - l0, r += bv[h].cnt0(n) - r0;
    }
    return res;
  }
#include "wavelet_count_less.hpp"
};
