#pragma once
//! @code
//!   bit.walk([&](int r, ll sum) -> bool {
//!     // sum = a[0] + a[1] + ... + a[r]
//!   });
//!   int r = bit.walk2(sum);
//!   // Returns min r s.t. sum of [0,r] >= sum
//!   // Returns n if sum of [0,n-1] < sum
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
    ll ret = 0;
    for (; i >= 0; (i &= i + 1)--) ret += s[i];
    return ret;
  }
  ll query(int l, int r) {
    return query(r) - query(l - 1);
  }
#include "bit_uncommon/walk_lambda.hpp"
#include "../data_structures_[l,r)/bit_uncommon/walk.hpp"
};
