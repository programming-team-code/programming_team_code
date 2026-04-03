#pragma once
//! @code
//!   bit.walk([&](int r, ll sum) -> bool {
//!     // sum = a[0] + a[1] + ... + a[r - 1]
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
#include "bit_uncommon/init.hpp"
  void update(int i, ll d) {
    for (; i < sz(s); i |= i + 1) s[i] += d;
  }
  ll query(int r) {
    ll ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  ll query(int l, int r) { return query(r) - query(l); }
#include "bit_uncommon/walk_lambda.hpp"
#include "bit_uncommon/walk.hpp"
};
