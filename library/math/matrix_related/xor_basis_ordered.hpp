#pragma once
const int lg = 60;
//! https://codeforces.com/blog/entry/68953
//! https://github.com/ssk4988/Hackpack/blob/main/content/numerical/XORBasis.h
//! @code
//!     basis<int> b;
//!     basis<ll> b;
//!     basis<bitset<lg>> b;
//! @endcode
//! can get tiny speed boost by repeatedly jumping to next
//! 1-bit in v with __lg
template<class T> struct basis {
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
