#pragma once
#include "manacher.hpp"
//! @time O(n + q)
//! @space O(n)
struct pal_query {
  vi man;
  pal_query(const auto& s): man(manacher(s)) {};
  bool is_pal(int l, int r) { // [l, r]
    return man[l + r] <= l;
  }
};
