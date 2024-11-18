#define PROBLEM \
  "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    string s;
    auto [_, _sa_inv, lcp] = get_sa(s, 256);
    assert(empty(lcp));
  }
  {
    string s = "a";
    auto [_, _sa_inv, lcp] = get_sa(s, 256);
    assert(empty(lcp));
  }
  string s;
  cin >> s;
  int n = sz(s);
  auto [sa, sa_inv, lcp] = get_sa(s, 256);
  sa_query sf_a(s, sa, sa_inv, lcp);
  mono_st_asserts(lcp);
  assert(sz(sa) == n);
  assert(sz(sa_inv) == n);
  assert(sz(lcp) == n - 1);
  {
    auto [sa_le, sa_ri, s_l, s_r] =
      sf_a.find_substrs_concated({});
    assert(sa_le == 0 && sa_ri == n);
    assert(s_r - s_l == 0);
  }
  {
    auto [sa_le, sa_ri, s_l, s_r] =
      sf_a.find_substrs_concated({{0, 0}});
    pair<int, int> short_res = sf_a.find_substr(0, 0);
    assert(sa_le == short_res.first &&
      sa_ri == short_res.second);
    assert(sa_le == 0 && sa_ri == n);
    assert(s_r - s_l == 0);
  }
  {
    auto [sa_le, sa_ri, s_l, s_r] =
      sf_a.find_substrs_concated({{0, 0}, {n - 1, n - 1}});
    pair<int, int> short_res =
      sf_a.find_substr(n - 1, n - 1);
    assert(sa_le == short_res.first &&
      sa_ri == short_res.second);
    assert(sa_le == 0 && sa_ri == n);
    assert(s_r - s_l == 0);
  }
  for (int i = 0; i < n; i++) {
    assert(sa[sa_inv[i]] == i);
    assert(sa_inv[sa[i]] == i);
  }
  for (auto val : sa) cout << val << " ";
  cout << '\n';
}
