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
  ll query(int i) { // [0, i]
    ll ret = 0;
    for (; i >= 0; (i &= i + 1)--) ret += s[i];
    return ret;
  }
  ll query(int l, int r) { // [l, r]
    return query(r) - query(l - 1);
  }
#include "bit_uncommon/walk.hpp"
};
