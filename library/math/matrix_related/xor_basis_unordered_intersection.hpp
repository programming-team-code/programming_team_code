#pragma once
#include "xor_basis_unordered.hpp"
//! https://github.com/suisen-cp/cp-library-cpp/blob/main/library/linear_algebra/xor_base.hpp
//! @time O(32^2) or O(64^2);
//! @space O(32) or O(64)
template<class T>
basis<T> intersection(const basis<T>& u,
  const basis<T>& v) {
  basic_string<array<T, 2>> w;
  for (T e : u.b) w += {e, e};
  basis<T> res;
  for (T e : v.b) {
    T s = 0;
    for (auto [x, y] : w)
      if ((e ^ x) < e) e ^= x, s ^= y;
    if (e) w += {e, s};
    else res.insert(s);
  }
  return res;
}
