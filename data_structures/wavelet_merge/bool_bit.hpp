//! @time O(n + q log n)
//! @space O(n)
struct BIT {
  vector<int64_t> s;
  BIT(int n): s(n) {}
  BIT(const vector<int64_t>& a): s(a) {
    for (int i = 0; i < ssize(a); i++) {
      int j = i | (i + 1);
      if (j < ssize(a)) s[j] += s[i];
    }
  }
  void update(int i, int64_t d) {
    for (; i < ssize(s); i |= i + 1) s[i] += d;
  }
  int64_t query(int r) { // [0, r)
    int64_t ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  int64_t query(int l, int r) { // [l, r)
    return query(r) - query(l);
  }
  //! Requires bit.query(i,i+1) >= 0
  //! @returns max pos such that sum of [0,pos) < sum
  int lower_bound(int64_t sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << __lg(ssize(s) | 1); pw; pw >>= 1)
      if (pos + pw <= ssize(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos;
  }
};
//! https://github.com/dacin21/dacin21_codebook/blob/master/trees/wavelet_matrix_updates.cpp
//! space efficient boolean array with range sum query, and
//! point update note `>> 6` is the same as `/ 64` note `&
//! 63` is the same as `% 64`
struct bool_bit {
  int n;
  vector<uint64_t> mask;
  BIT presum = {0};
  //! @param a boolean array
  //! @time O(n)
  //! @space O(n / 64)
  bool_bit(const vector<bool>& a):
    n(ssize(a)), mask(n / 64 + 1) {
    vector<int64_t> init((n + 63) / 64);
    for (int i = 0; i < n; i++) {
      mask[i >> 6] |= (uint64_t(a[i]) << (i & 63));
      init[i >> 6] += a[i];
    }
    presum = {init};
  }
  //! @param i defines range [0, i)
  //! @returns a[0] + a[1] + ... + a[i - 1]
  //! @time O(log(n / 64))
  //! @space O(1)
  int popcount(int i) {
    return presum.query(i >> 6) +
      __builtin_popcountll(
        mask[i >> 6] & ((1ULL << (i & 63)) - 1));
  }
  //! @param l,r defines range [l, r)
  //! @returns a[l] + a[l + 1] + ... + a[r - 1]
  //! @time O(log(n / 64))
  //! @space O(1)
  int popcount(int l, int r) {
    return popcount(r) - popcount(l);
  }
  //! @param i index
  //! @returns 1 iff index i is active
  //! @time O(1)
  //! @space O(1)
  bool on(int i) { return (mask[i >> 6] >> (i & 63)) & 1; }
  //! @param i index
  //! @param new_num we want to set a[i] = new_num
  //! @time O(log(n / 64))
  //! @space O(1)
  void set(int i, bool new_num) {
    if (on(i) != new_num) {
      mask[i >> 6] ^= 1ULL << (i & 63);
      presum.update(i >> 6, new_num ? 1 : -1);
    }
  }
};
