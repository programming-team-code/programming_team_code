#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/wildcard_pattern_matching"
#include "../template.hpp"
#include "../../../library/strings/wildcard_pattern_matching.hpp"
using vl = vector<ll>;
namespace ignore {
#include "../../../kactl/content/number-theory/ModPow.h"
}
ll modpow(ll a, ll e);
#include "../../../kactl/content/numerical/NumberTheoreticTransform.h"
ll modpow(ll a, ll e) {
  if (e == 0) return 1;
  ll x = modpow(a * a % mod, e >> 1);
  return e & 1 ? x * a % mod : x;
}
vl to_vec(const string& s) {
  int n = sz(s);
  vl res(n);
  for (int i = 0; i < n; i++)
    if (s[i] == '*') res[i] = 0;
    else res[i] = s[i] - 'a' + 1;
  return res;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string haystack, needle;
  cin >> haystack >> needle;
  auto haystack_vec = to_vec(haystack);
  auto needle_vec = to_vec(needle);
  auto matches = wildcard_pattern_matching(haystack_vec,
    needle_vec, conv);
  for (bool b : matches) cout << b;
  cout << '\n';
  return 0;
}
