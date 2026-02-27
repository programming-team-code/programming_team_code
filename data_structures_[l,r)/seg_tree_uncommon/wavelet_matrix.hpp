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
//! https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp
//! @code
//!   vector<ll> a(n);
//!   wavelet_matrix wm(a, 30); // 0 <= a[i] < (1<<30)
//!   wm.kth(l, r, k); //(k+1)th smallest number in [l,r)
//!   wm.kth(l, r, 0); //min in [l,r)
//! @endcode
//! @time O(n * lg + q * lg)
//! @space O(n * lg / 64)
struct wavelet_matrix {
  int n;
  vector<bit_vec> bv;
  wavelet_matrix(vector<int64_t> a, int lg):
    n(ssize(a)), bv(lg, {{}}) {
    for (int h = ssize(bv); h--;) {
      vector<bool> b(n);
      for (int i = 0; i < n; i++) b[i] = (~a[i] >> h) & 1;
      bv[h] = b;
      ranges::stable_partition(a,
        [&](int64_t x) { return (~x >> h) & 1; });
    }
  }
  int64_t kth(int l, int r, int k) {
    int64_t res = 0;
    for (int h = ssize(bv); h--;) {
      int x = bv[h].cnt(l), y = bv[h].cnt(r);
      if (k < y - x) l = x, r = y;
      else
        k -= y - x, res += 1LL << h, l += bv[h].cnt(n) - x,
          r += bv[h].cnt(n) - y;
    }
    return res;
  }
  //! count of i in [l..r) such that a[i] < ub
  //! @time O(lg)
  //! @space O(1)
  int count(int l, int r, int64_t ub) {
    int res = 0;
    for (int h = ssize(bv); h--;) {
      int x = bv[h].cnt(l), y = bv[h].cnt(r);
      if ((ub >> h) & 1)
        res += y - x, l += bv[h].cnt(n) - x,
          r += bv[h].cnt(n) - y;
      else l = x, r = y;
    }
    return res;
  }
};
