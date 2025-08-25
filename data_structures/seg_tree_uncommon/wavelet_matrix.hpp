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
  bit_vec(const vector<bool>& a): b(ssize(a) / 64 + 1) {
    for (int i = 0; i < ssize(a); i++) {
      auto& [x, y] = b[i >> 6];
      x |= ull(a[i]) << (i & 63), y += a[i];
    }
    for (int i = 1; i < ssize(b); i++)
      b[i].second += b[i - 1].second;
  }
  int cnt(int r) {
    auto [x, y] = b[r >> 6];
    return y - popcount(x & -1ULL << (r & 63));
  }
};
//! @code
//!   vector<ull> a(n);
//!   wavelet_matrix wm(a, 1e9); // requires a[i] <= 1e9
//!   wm.kth(l, r, k); //(k+1)th smallest number in [l,r)
//!   wm.kth(l, r, 0); //min in [l,r)
//! @endcode
//! @time O(n * log(max_val) + q * log(max_val))
//! @space O(n * log(max_val) / 64)
struct wavelet_matrix {
  int n;
  vector<bit_vec> bv;
  wavelet_matrix(vector<ull> a, ull max_val):
    n(ssize(a)), bv(bit_width(max_val), {{}}) {
    for (int h = ssize(bv); h--;) {
      int i = 0;
      vector<bool> b(n);
      ranges::stable_partition(a,
        [&](ull x) { return b[i++] = (~x >> h) & 1; });
      bv[h] = b;
    }
  }
  ull kth(int l, int r, int k) {
    int64_t res = 0;
    for (int h = ssize(bv); h--;) {
      int l0 = bv[h].cnt(l), r0 = bv[h].cnt(r);
      if (k < r0 - l0) l = l0, r = r0;
      else
        k -= r0 - l0, res |= 1ULL << h,
          l += bv[h].cnt(n) - l0, r += bv[h].cnt(n) - r0;
    }
    return res;
  }
  //! count of i in [l..r) such that a[i] < ub
  //! @time O(log(max_val))
  //! @space O(1)
  int count(int l, int r, ull ub) {
    int res = 0;
    for (int h = ssize(bv); h--;) {
      int l0 = bv[h].cnt(l), r0 = bv[h].cnt(r);
      if ((~ub >> h) & 1) l = l0, r = r0;
      else
        res += r0 - l0, l += bv[h].cnt(n) - l0,
          r += bv[h].cnt(n) - r0;
    }
    return res;
  }
};
