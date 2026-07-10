#pragma once
//! @code
//!   BIT bit(n);
//!   int r = bit.walk(sum);
//!   // Returns min r s.t. sum of [0,r] >= sum
//!   // Returns n if sum of [0,n-1] < sum
//!   // Returns -1 if sum <= 0
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
// NOLINTNEXTLINE(readability-identifier-naming)
struct BIT {
  vector<ll> s;
  BIT(int n): s(n) {}
#include "../data_structures_[l,r)/bit_uncommon/init.hpp"
  void update(int i, ll d) {
    for (; i < sz(s); i |= i + 1) s[i] += d;
  }
  ll query(int i) {
    ll res = 0;
    for (; i >= 0; (i &= i + 1)--) res += s[i];
    return res;
  }
  ll query(int l, int r) {
    return query(r) - query(l - 1);
  }
#include "../data_structures_[l,r)/bit_uncommon/walk.hpp"
};
