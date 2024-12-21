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
struct wavelet_matrix {
  int n;
  vector<bit_vec> bv;
  //! Requires a[i] <= max_val
  //! @time O(n * log(max_val))
  //! @space O(n * log(max_val) / 64)
  wavelet_matrix(vector<uint64_t> a, uint64_t max_val):
    n(ssize(a)), bv(bit_width(max_val), {{}}) {
    vector<uint64_t> nxt(n);
    for (int h = ssize(bv); h--;) {
      vector<bool> b(n);
      for (int i = 0; i < n; i++) b[i] = (a[i] >> h) & 1;
      bv[h] = b;
      array it{begin(nxt), begin(nxt) + bv[h].cnt0(n)};
      for (int i = 0; i < n; i++) *it[b[i]]++ = a[i];
      swap(a, nxt);
    }
  }
  //! (k+1)th smallest number in [l,r)
  //! kth(l,r,0) returns the min
  //! @time O(log(max_val))
  //! @space O(1)
  uint64_t kth(int l, int r, int k) {
    int64_t res = 0;
    for (int h = ssize(bv); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if (k < r0 - l0) l = l0, r = r0;
      else
        k -= r0 - l0, res |= 1ULL << h,
          l += bv[h].cnt0(n) - l0, r += bv[h].cnt0(n) - r0;
    }
    return res;
  }
  //! count of i in [l..r) such that a[i] < ub
  //! @time O(log(max_val))
  //! @space O(1)
  int count(int l, int r, uint64_t ub) {
    int res = 0;
    for (int h = ssize(bv); h--;) {
      int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
      if ((~ub >> h) & 1) l = l0, r = r0;
      else
        res += r0 - l0, l += bv[h].cnt0(n) - l0,
          r += bv[h].cnt0(n) - r0;
    }
    return res;
  }
};
