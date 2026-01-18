#pragma once
//! @code
//!   vector<bool> a(n);
//!   bit_vec bv(a);
//!   bv.cnt(r); // a[0] + a[1] + ... + a[r - 1]
//! @endcode
//! @time O(n + q)
//! @space O(n / 64)
using ull = uint64_t;
struct bit_vec {
  vector<pair<ull, int>> b;
  bit_vec(const vector<bool>& a): b(sz(a) / 64 + 1) {
    rep(i, 0, sz(a)) {
      auto& [x, y] = b[i >> 6];
      x |= ull(a[i]) << (i & 63), y += a[i];
    }
    rep(i, 1, sz(b)) b[i].second += b[i - 1].second;
  }
  int cnt(int r) {
    auto [x, y] = b[r >> 6];
    return y - popcount(x & -1ULL << (r & 63));
  }
};
