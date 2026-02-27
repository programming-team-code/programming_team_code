//! https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
//! @code
//!   // requires s[i]>=0
//!   string s;
//!   auto [sa, sa_inv, lcp] = sa_short(s);
//!   vi s_vec;
//!   auto [sa1, sa_inv1, lcp1] = sa_short(s_vec);
//! @endcode
//! about 2-3x slower than KACTL
//! @time O(n * log^2(n))
//! @space O(n)
auto sa_short(const auto& s) {
  int n = ssize(s), b = 6;
  vector<int> sa(n), sa_inv(begin(s), end(s)), lcp(n - 1),
    t(n);
  iota(begin(sa), end(sa), 0);
  for (int j = 1; j <= n; j *= b) {
    swap(t, sa_inv);
    auto cmp = [&](int i1, int i2) {
      for (int k = 0; k < b; k++) {
        int x = i1 + j * k < n ? t[i1 + j * k] : -1;
        int y = i2 + j * k < n ? t[i2 + j * k] : -1;
        if (x != y) return x < y;
      }
      return false;
    };
    stable_sort(begin(sa), end(sa), cmp);
    sa_inv[sa[0]] = 0;
    for (int i = 1; i < n; i++)
      sa_inv[sa[i]] =
        sa_inv[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
  }
  int l = 0;
  for (int i = 0; i < n; i++) {
    if (l > 0) l--;
    if (sa_inv[i] == 0) continue;
    int j = sa[sa_inv[i] - 1];
    while (max(i, j) + l < n && s[i + l] == s[j + l]) l++;
    lcp[sa_inv[i] - 1] = l;
  }
  return tuple{sa, sa_inv, lcp};
}
