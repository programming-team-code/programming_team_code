#pragma once
#include "manacher.hpp"
//! @time O(n + q)
//! @space O(n)
template<class T> struct pal_query {
  vi man;
  pal_query(const T& s): man(manacher(s)) {};
  bool is_pal(int le, int ri) { // [le, ri]
    return man[le + ri] <= le;
  }
};
