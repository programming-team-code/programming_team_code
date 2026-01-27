#define PROBLEM \
  "https://judge.yosupo.jp/problem/suffixarray"
// just because with debug mode, test runs in 30s, and
// there's like 30 tests
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array_short.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  auto [sa, sa_inv, lcp] = sa_short(vi(all(s)));
  rep(i, 0, sz(s)) {
    assert(sa[sa_inv[i]] == i);
    assert(sa_inv[sa[i]] == i);
  }
  vi lcp_kasai(sz(s) - 1);
  int sz = 0;
  rep(i, 0, sz(s)) {
    if (sz > 0) sz--;
    if (sa_inv[i] == 0) continue;
    for (int j = sa[sa_inv[i] - 1];
      max(i, j) + sz < sz(s) && s[i + sz] == s[j + sz];)
      sz++;
    lcp_kasai[sa_inv[i] - 1] = sz;
  }
  assert(lcp == lcp_kasai);
  for (int val : sa) cout << val << " ";
  cout << '\n';
}
