//! @code
//!   vector<bool> a(n);
//!   bit_vec bv(a);
//!   bv.cnt(r); // a[0] + a[1] + ... + a[r - 1]
//! @endcode
//! @time O(n + q)
//! @space O(n / 64)
struct bit_vec {
  vector<pair<uint64_t, int>> b;
  bit_vec(const vector<bool>& a): b(ssize(a) / 64 + 1) {
    for (int i = 0; i < ssize(a); i++) {
      auto& [x, y] = b[i >> 6];
      x |= uint64_t(a[i]) << (i & 63), y += a[i];
    }
    for (int i = 1; i < ssize(b); i++)
      b[i].second += b[i - 1].second;
  }
  int cnt(int r) {
    auto [x, y] = b[r >> 6];
    return y - popcount(x & -1ULL << (r & 63));
  }
};
