#pragma once
//! https://codeforces.com/blog/entry/68953
//! https://github.com/ssk4988/Hackpack/blob/main/content/numerical/XORBasis.h
//! @code
//!   const int B = 30;
//!   xor_basis<B> b;
//!   bitset<B> v;
//!   bool in_span = b.shrink(v) >= 0;
//!   b.insert(v);
//!   bitset<B> k = 5; // 0 <= k < (1 << npivot)
//!   bitset<B> kth = b.walk(k);
//!   // (k+1)-th smallest vector in span
//!   // k=0 gives smallest vector in span
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
