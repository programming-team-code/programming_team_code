#pragma once
//! https://codeforces.com/blog/entry/68953
//! https://codeforces.com/blog/entry/100066?#comment-887897
//! @code
//!   basis<int> b1;
//!   basis<ll> b2;
//!   basis<dynamic_bitset<>> b3;
//! @endcode
//! b.shrink(v) == b.shrink(b.shrink(v))
//! for x in b.b: (bit_floor(x)&b.shrink(v))==0
//! for 0<=i<j<sz(b.b): (bit_floor(b[i])&b[j])==0
//! @time O(32) or O(64)
//! @space O(32) or O(64)
template<class T> struct basis {
  vector<T> b;
  T shrink(T v) {
    for (T x : b) v = min(v, v ^ x);
    return v;
  }
  bool insert(T v) {
    return (v = shrink(v)) ? b.push_back(v), 1 : 0;
  }
};
