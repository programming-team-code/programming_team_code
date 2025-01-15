struct bit_vec {
  vector<pair<uint64_t, int>> b;
  //! @time O(n)
  //! @space O(n / 64)
  bit_vec(const vector<bool>& a): b(ssize(a) / 64 + 1) {
    for (int i = 0; i < ssize(a); i++)
      b[i >> 6].first |= uint64_t(a[i]) << (i & 63);
    for (int i = 0; i < ssize(b) - 1; i++)
      b[i + 1].second = popcount(b[i].first) + b[i].second;
  }
  //! @returns !a[0] + !a[1] + ... + !a[r - 1]
  //! @time O(1)
  //! @space O(1)
  int cnt0(int r) {
    auto [x, y] = b[r >> 6];
    return r - y - popcount(x & ((1ULL << (r & 63)) - 1));
  }
};
