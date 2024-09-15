//! @file
#pragma once
#include "manacher.hpp"
template <class T> struct pal_query {
  int n;
  vi man;
  pal_query(const T& s) : n(sz(s)), man(manacher(s)){};
  //! @param le,ri defines substring [le,ri]
  //! @returns 1 iff s.substr(le, ri - le + 1) is a palindrome
  //! @time O(1)
  //! @space O(1)
  bool is_pal(int le, int ri) {
    return man[le + ri] <= le;
  }
};
