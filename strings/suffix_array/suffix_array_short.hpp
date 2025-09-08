//! https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
//! @code
//!   // requires s[i]>=0
//!   string s;
//!   auto [sa, sa_inv, lcp] = sa_short(s);
//!   vi s_vec;
//!   auto [sa1, sa_inv1, lcp1] = sa_short(s_vec);
//! @endcode
//! runs in ~1.5s for 5e5
//! @time O(n * log^2(n))
//! @space O(n)
auto sa_short(const auto& s) {
  int n = ssize(s);
  vector<int> sa(n), sa_inv(begin(s), end(s)), lcp(n - 1);
  iota(begin(sa), end(sa), 0);
  for (int k = 1; k <= n; k *= 2) {
    vector<int> x(sa_inv);
    auto proj = [&](int i) {
      return pair(x[i], i + k < n ? x[i + k] : -1);
    };
    ranges::sort(sa, {}, proj);
    sa_inv[sa[0]] = 0;
    for (int i = 1; i < n; i++)
      sa_inv[sa[i]] = sa_inv[sa[i - 1]] +
        (proj(sa[i - 1]) != proj(sa[i]));
  }
  int sz = 0;
  for (int i = 0; i < n; i++) {
    if (sz > 0) sz--;
    if (sa_inv[i] == 0) continue;
    for (int j = sa[sa_inv[i] - 1];
      max(i, j) + sz < n && s[i + sz] == s[j + sz];)
      sz++;
    lcp[sa_inv[i] - 1] = sz;
  }
  return tuple{sa, sa_inv, lcp};
}
