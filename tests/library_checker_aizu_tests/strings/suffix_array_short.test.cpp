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
  auto [sa, sa_inv, _] = sa_short(s);
  for (int i = 0; i < sz(s); i++) {
    assert(sa[sa_inv[i]] == i);
    assert(sa_inv[sa[i]] == i);
  }
  for (int val : sa) cout << val << " ";
  cout << '\n';
}
