#pragma once
//! https://codeforces.com/blog/entry/68953
//! https://github.com/ssk4988/Hackpack/blob/main/content/numerical/XORBasis.h
//! @code
//!   basis_ordered<int> b3;
//!   basis_ordered<ll> b4;
//!   basis_ordered<bitset<lg>> b5;
//! @endcode
const int lg = 60;
template<class T> struct basis_ordered {
  T b[lg]{};
  int siz = 0;
  int shrink(T& v) {
    for (int i = lg - 1; i >= 0; i--)
      if (((v >> i) & T(1)) != T(0)) {
        if (b[i] == T(0)) return i;
        v ^= b[i];
      }
    return -1;
  }
  bool insert(T v) {
    int i = shrink(v);
    return i >= 0 ? b[i] = v, ++siz : 0;
  }
};
