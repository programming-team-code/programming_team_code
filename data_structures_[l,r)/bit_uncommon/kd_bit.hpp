//! https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/data-structures/KDBIT.h
//! @code
//!   KD_BIT<2> bit(n, m);
//!   bit.update(i, j, 5);
//!   // 0 <= i < n
//!   // 0 <= j < m
//!   bit.query(i1, i2, j1, j2);
//!   // 0 <= i1 <= i2 <= n
//!   // 0 <= j1 <= j2 <= m
//! @endcode
//! @time O(n^k + q * log^k n)
//! @space O(n^k)
template<int K> struct KD_BIT {
  vector<KD_BIT<K - 1>> s;
  KD_BIT(int n, auto... a): s(n, KD_BIT<K - 1>(a...)) {}
  void update(int i, auto... a) {
    for (; i < ssize(s); i |= i + 1) s[i].update(a...);
  }
  int64_t query(int l, int r, auto... a) {
    int64_t ans = 0;
    for (; l < r; r &= r - 1) ans += s[r - 1].query(a...);
    for (; r < l; l &= l - 1) ans -= s[l - 1].query(a...);
    return ans;
  }
};
template<> struct KD_BIT<0> {
  int64_t s = 0;
  void update(int64_t v) { s += v; }
  int64_t query() { return s; }
};
