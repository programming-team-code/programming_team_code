//! https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixArray.h
//!
//! 0 banana 3
//! 1 anana  2
//! 2 nana   5
//! 3 ana    1
//! 4 na     4
//! 5 a      0
//!
//! 5 a      0
//!   |
//! 3 ana    1
//!   |||
//! 1 anana  2
//!
//! 0 banana 3
//!
//! 4 na     4
//!   ||
//! 2 nana   5
//!
//! sa = {5, 3, 1, 0, 4, 2}
//! sa_inv = {3, 2, 5, 1, 4, 0}
//! lcp = {1, 3, 0, 0, 2}
//!
//! @code
//!   auto [sa, sa_inv, lcp] = get_sa(s, 256);
//! @endcode
//!
//! requires 0<=s[i]<max_num
//!
//! @time O(nlogn + max_num)
//! @space O(n + max_num)
template<class T>
array<vector<int>, 3> get_sa(const T& s, int max_num) {
  int n = ssize(s);
  vector<int> sa(n), sa_inv(begin(s), end(s)),
    lcp(max(0, n - 1));
  iota(begin(sa), end(sa), 0);
  for (int ln = 0; ln < n; ln = max(1, 2 * ln)) {
    vector<int> tmp(n), freq(max_num);
    iota(begin(tmp), begin(tmp) + ln, n - ln);
    copy_if(begin(sa), end(sa), begin(tmp) + ln,
      [&](int& x) { return (x -= ln) >= 0; });
    for (int x : sa_inv) freq[x]++;
    partial_sum(begin(freq), end(freq), begin(freq));
    for_each(rbegin(tmp), rend(tmp),
      [&](int x) { sa[--freq[sa_inv[x]]] = x; });
    swap(sa_inv, tmp);
    max_num = 1, sa_inv[sa[0]] = 0;
    auto prev_inv = [&](int i) {
      return pair(tmp[i], i + ln < n ? tmp[i + ln] : -1);
    };
    for (int i = 1; i < n; i++) {
      max_num += prev_inv(sa[i - 1]) != prev_inv(sa[i]);
      sa_inv[sa[i]] = max_num - 1;
    }
    if (max_num == n) break;
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
  return {sa, sa_inv, lcp};
}
