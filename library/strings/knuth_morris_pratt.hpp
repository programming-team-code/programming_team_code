#pragma once
#include "prefix_function.hpp"
//! @code
//!   string t;
//!   KMP kmp(t);
//!   vi t;
//!   KMP kmp(t);
//!   auto match = kmp.find_str(s)
//! @endcode
//! s[match[i],sz(t)) == t
//! @time O(|s| + |t|)
//! @space O(|s| + |t|)
// NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct KMP {
  T needle;
  vi pi;
  KMP(const T& a_needle):
    needle(a_needle), pi(prefix_function(needle)) {}
  vi find_str(const T& haystack) {
    vi matches;
    int j = 0;
    rep(i, 0, sz(haystack)) {
      while (j > 0 && needle[j] != haystack[i])
        j = pi[j - 1];
      j += (needle[j] == haystack[i]);
      if (j == sz(needle)) {
        matches.push_back(i - sz(needle) + 1);
        j = pi[j - 1];
      }
    }
    return matches;
  }
};
