#pragma once
#include "prefix_function.hpp"
//! @code
//!   KMP kmp(t);
//!   auto match = kmp.find_str(s);
//! @endcode
//! s[match[i],sz(t)) == t
//! @time O(|s| + |t|)
//! @space O(|s| + |t|)
// NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct KMP {
  T t;
  vi pi;
  KMP(const T& a_t):
    t(a_t), pi(prefix_function(t)) {}
  vi find_str(const T& s) {
    vi matches;
    int j = 0;
    rep(i, 0, sz(s)) {
      while (j > 0 && t[j] != s[i])
        j = pi[j - 1];
      j += (t[j] == s[i]);
      if (j == sz(t)) {
        matches.push_back(i - sz(t) + 1);
        j = pi[j - 1];
      }
    }
    return matches;
  }
};
