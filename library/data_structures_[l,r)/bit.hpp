#pragma once
//! @time O(n + q log n)
//! @space O(n)
// NOLINTNEXTLINE(readability-identifier-naming)
struct BIT {
  vector<ll> s;
  BIT(int n): s(n) {}
#include "bit_uncommon/init.hpp"
  void update(int i, ll d) {
    for (; i < sz(s); i |= i + 1) s[i] += d;
  }
  ll query(int r) { // [0, r)
    ll ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  ll query(int l, int r) { // [l, r)
    return query(r) - query(l);
  }
#include "bit_uncommon/walk.hpp"
};
