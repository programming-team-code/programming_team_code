#pragma once
struct bitset_sum {
  vector<uint64_t> mask;
  vi pref;
  //! @time O(n)
  //! @space O(n / 64)
  bitset_sum(const vector<bool>& a):
    mask(sz(a) / 64 + 1), pref(sz(mask)) {
    rep(i, 0, sz(a)) mask[i >> 6] |=
      (uint64_t(a[i]) << (i & 63));
    rep(i, 0, sz(mask) - 1) pref[i + 1] =
      popcount(mask[i]) + pref[i];
  }
  //! @param i defines range [0, i)
  //! @returns a[0] + a[1] + ... + a[i - 1]
  //! @time O(1)
  //! @space O(1)
  int pref_sum(int i) {
    return pref[i >> 6] +
      popcount(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
  }
  //! @param i index
  //! @returns 1 iff a[i] was on
  //! @time O(1)
  //! @space O(1)
  bool on(int i) { return (mask[i >> 6] >> (i & 63)) & 1; }
};
