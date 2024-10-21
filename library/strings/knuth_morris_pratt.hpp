#pragma once
#include "prefix_function.hpp"
//! @code
//!   KMP kmp(t);
//!   auto match = kmp.find_str(s);
//! @endcode
//! if match[i] is true then s[i,sz(t)) == t
//! @time O(|s| + |t|)
//! @space O(|s| + |t|)
// NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct KMP {
  T t;
  vi pi;
  KMP(const T& a_t): t(a_t), pi(prefix_function(t)) {}
  vector<bool> find_str(const T& s) {
    vector<bool> is_m(sz(s));
    int j = 0;
    rep(i, 0, sz(s)) {
      while (j && s[i] != t[j]) j = pi[j - 1];
      j += (s[i] == t[j]);
      if (j == sz(t)) {
        is_m[i - j + 1] = 1;
        j = pi[j - 1];
      }
    }
    return is_m;
  }
};
