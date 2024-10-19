#pragma once
//! @time O(n + q log n)
//! @space O(n)
// NOLINTNEXTLINE(readability-identifier-naming)
struct BIT {
  vector<ll> s;
  BIT(int n): s(n) {}
#include "bit_uncommon/vector_constructor.hpp"
  void update(int i, ll d) {
    for (; i < sz(s); i |= i + 1) s[i] += d;
  }
  ll query(int ri) { // [0, ri)
    ll ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  ll query(int le, int ri) { // [le, ri)
    return query(ri) - query(le);
  }
#include "bit_uncommon/lower_bound.hpp"
};
