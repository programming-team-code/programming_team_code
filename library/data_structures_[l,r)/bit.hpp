#pragma once
//! @code
//!   BIT bit(n);
//!   bit.walk([&](int r, int64_t sum) -> bool {
//!     // sum = a[0] + a[1] + ... + a[r - 1]
//!   });
//!   int r = bit.walk2(sum);
//!   // Returns min r s.t. sum of [0,r+1) >= sum
//!   // Returns n if sum of [0,n) < sum
//!   // Returns -1 if sum <= 0
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
    ll res = 0;
    for (; r > 0; r &= r - 1) res += s[r - 1];
    return res;
  }
  ll query(int l, int r) { return query(r) - query(l); }
#include "bit_uncommon/walk.hpp"
};
