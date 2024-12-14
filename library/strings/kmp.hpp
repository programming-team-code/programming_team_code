#pragma once
#include "prefix_function.hpp"
//! @code
//!   string s,t;
//!   KMP kmp(t);
//!   auto match = kmp.find_str(s);
//!   vi s_vec,t_vec;
//!   KMP kmp1(t_vec);
//!   auto match2 = kmp1.find_str(s_vec);
//! @endcode
//! if match[i] == 1 then s[i,sz(t)) == t
//! @time O(|s| + |t|)
//! @space O(|s| + |t|)
// NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct KMP {
  T t;
  vi pi;
  KMP(const T& t): t(t), pi(prefix_function(t)) {}
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
