#pragma once
struct bit_vec {
  vector<pair<uint64_t, int>> b;
  //! @time O(n)
  //! @space O(n / 64)
  bit_vec(const vector<bool>& a): b(sz(a) / 64 + 1) {
    rep(i, 0, sz(a)) b[i >> 6].first |=
      (uint64_t(a[i]) << (i & 63));
    rep(i, 0, sz(b) - 1) b[i + 1].second =
      popcount(b[i].first) + b[i].second;
  }
  //! @returns !a[0] + !a[1] + ... + !a[i - 1]
  //! @time O(1)
  //! @space O(1)
  int cnt0(int i) {
    auto [x, y] = b[i >> 6];
    return i - y - popcount(x & ((1ULL << (i & 63)) - 1));
  }
};
