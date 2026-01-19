#pragma once
#include "xor_basis_unordered.hpp"
//! https://github.com/suisen-cp/cp-library-cpp/blob/main/library/linear_algebra/xor_base.hpp
//! @time O(32^2) or O(64^2);
//! @space O(32) or O(64)
basis intersection(const basis& u, const basis& v) {
  vector<pii> w(sz(u.b));
  rep(i, 0, sz(w)) w[i] = {u.b[i], u.b[i]};
  basis res;
  for (int e : v.b) {
    int s = 0;
    for (auto [x, y] : w)
      if ((e ^ x) < e) e ^= x, s ^= y;
    if (e) w.emplace_back(e, s);
    else res.insert(s);
  }
  return res;
}
