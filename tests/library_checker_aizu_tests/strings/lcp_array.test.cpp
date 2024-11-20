#define PROBLEM \
  "https://judge.yosupo.jp/problem/number_of_substrings"
// just because with debug mode, test runs in 30s, and
// there's like 30 tests
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array.hpp"
#include "../../../library/strings/suffix_array/suffix_array_short.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    // to test commented example
    string s = "banana";
    auto [sa, sa_inv, lcp] = get_sa(s, 256);
    assert(sa == vector<int>({5, 3, 1, 0, 4, 2}));
    assert(sa_inv == vector<int>({3, 2, 5, 1, 4, 0}));
    assert(lcp == vector<int>({1, 3, 0, 0, 2}));
  }
  string s;
  cin >> s;
  int n = sz(s);
  auto [sa, sa_inv, lcp] = get_sa(s, 256);
  auto [sa1, sa_inv1, lcp1] = sa_short(s);
  assert(sa == sa1);
  assert(sa_inv == sa_inv1);
  assert(lcp == lcp1);
  assert(sz(lcp) == n - 1);
  cout << 1LL * n * (n + 1) / 2 -
      accumulate(begin(lcp), end(lcp), 0LL)
       << '\n';
}
