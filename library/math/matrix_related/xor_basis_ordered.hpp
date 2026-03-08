#pragma once
//! https://codeforces.com/blog/entry/68953
//! https://github.com/ssk4988/Hackpack/blob/main/content/numerical/XORBasis.h
//! @code
//!   basis_ordered<int> b1;
//!   basis_ordered<ll> b2;
//!   basis_ordered<bitset<lg>> b3;
//!   b2.insert(x); // 0 <= x < (1LL<<B)
//! @endcode
//! @time O(q * B^2/32)
//! @space O(B^2/32)
template<int B> struct xor_basis {
  bitset<B> basis[B];
  int npivot = 0, nfree = 0;
  int shrink(bitset<B>& v) {
    for (int i = B; i--;)
      if (v[i]) {
        if (!basis[i][i]) return i;
        v ^= basis[i];
      }
    return -1;
  }
  bool insert(bitset<B>& v) {
    int i = shrink(v);
    return i >= 0 ? basis[i] = v, ++npivot : !++nfree;
  }
#include "walk.hpp"
};
