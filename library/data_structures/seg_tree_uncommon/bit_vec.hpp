#pragma once
using ull = uint64_t;
struct bit_vec {
  vector<pair<ull, int>> b;
  //! @time O(n)
  //! @space O(n / 64)
  bit_vec(const vector<bool>& a): b(sz(a) / 64 + 1) {
    rep(i, 0, sz(a)) b[i >> 6].first |= ull(a[i])
      << (i & 63);
    rep(i, 0, sz(b) - 1) b[i + 1].second =
      popcount(b[i].first) + b[i].second;
  }
  //! @returns !a[0] + !a[1] + ... + !a[r - 1]
  //! @time O(1)
  //! @space O(1)
  int cnt0(int r) {
    auto [x, y] = b[r >> 6];
    return r - y - popcount(x & ((1ULL << (r & 63)) - 1));
  }
};
