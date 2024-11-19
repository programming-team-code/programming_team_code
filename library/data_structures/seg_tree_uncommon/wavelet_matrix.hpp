#pragma once
#include "bitset_prefix_sum.hpp"
struct wavelet_matrix {
  int n;
  vector<bitset_sum> bv;
  //! Requires 0 <= a[i] < max_val
  wavelet_matrix(const vector<ll>& a, ll max_val):
    n(sz(a)),
    bv(bit_width(unsigned(max_val)), vector<bool>()) {
    vector<ll> cur(a), nxt(n);
    for (int h = sz(bv); h--;) {
      vector<bool> b(n);
      rep(i, 0, n) b[i] = (cur[i] >> h) & 1;
      bv[h] = b;
      array it{
        begin(nxt), begin(nxt) + (n - bv[h].pref_sum(n))};
      rep(i, 0, n) * it[b[i]]++ = cur[i];
      swap(cur, nxt);
    }
  }
  // find kth element in [l, r), 0 indexed
  ll kth(int l, int r, int k) {
    ll res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = l - bv[h].pref_sum(l),
          r0 = r - bv[h].pref_sum(r);
      if (k < r0 - l0) l = l0, r = r0;
      else {
        k -= r0 - l0;
        res |= 1LL << h;
        l += n - bv[h].pref_sum(n) - l0;
        r += n - bv[h].pref_sum(n) - r0;
      }
    }
    return res;
  }
  // count i in [l..r) satisfying a[i] < ub
  /*
  int count(int l, int r, ll ub) {
    int res = 0;
    for (int h = sz(bv); h--;) {
      int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (~ub >> h & 1)
        l = l0, r = r0;
      else {
        res += r0 - l0;
        l += bv[h].zeros - l0;
        r += bv[h].zeros - r0;
      }
    }
    return res;
  }
  */
};
