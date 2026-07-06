#define PROBLEM \
  "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  int n = sz(s);
  s = s + '$' + string(rbegin(s), rend(s));
  auto [sa, sa_inv, lcp] = get_sa(vi(all(s)), 256);
  sa_query lq(vi(all(s)), sa, sa_inv, lcp);
  rep(i, 0, n) rep(j, i, min(i + 2, n)) cout
    << lq.len_lcp(j, (n - i - 1) + n + 1) * 2 - (i == j)
    << " ";
  cout << '\n';
  return 0;
}
