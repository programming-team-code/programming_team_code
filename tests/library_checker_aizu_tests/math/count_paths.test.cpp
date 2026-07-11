#define PROBLEM \
  "https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences"
#include "../template.hpp"
#define const ;
#define mod mod_different_name
#include "../../../library/math/n_choose_k/grow.hpp"
#undef const
#undef mod
#define mod mod_not_using
#define modpow modpow_not_using
#include "../../../kactl/content/number-theory/ModPow.h"
#undef mod
#undef modpow
ll modpow(ll b, ll e) {
  ll res = 1;
  for (; e; b = b * b % 998'244'353, e >>= 1)
    if (e & 1) res = res * b % 998'244'353;
  return res;
}
#include "../../../library/math/count_paths/count_paths_triangle.hpp"
ll count_between_two_sequences(const vl& a, const vl& b) {
  int n = sz(a);
  vl dp(b[0] - a[0]);
  dp[0] = 1;
  for (int i = 0; i < n;) {
    int j = i;
    {
      vl h(b[i] - a[i]);
      rep(num, a[i], b[i]) {
        while (j < n && a[j] <= num) j++;
        h[num - a[i]] = j - i;
      }
      assert(sz(dp) <= sz(h));
      while (sz(dp) < sz(h)) dp.push_back(0);
      dp = divide_and_conquer(h, dp);
    }
    {
      vl h(j - i);
      rep(k, i, j) h[k - i] = b[k] - b[i];
      if (h.back() == 0) break;
      dp = divide_and_conquer(h, dp);
      if (j < n)
        dp = vl(begin(dp) + (a[j] - b[i]), end(dp));
    }
    i = j;
  }
  return dp.back();
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  mod_different_name = 998'244'353;
  int n, m;
  cin >> n >> m;
  vl a(n), b(n);
  rep(i, 0, n) cin >> a[i];
  rep(i, 0, n) cin >> b[i];
  rep(i, 1, n) a[i] = max(a[i], a[i - 1]);
  for (int i = n - 2; i >= 0; i--)
    b[i] = min(b[i], b[i + 1]);
  rep(i, 0, n) {
    if (a[i] >= b[i]) {
      cout << 0 << '\n';
      return 0;
    }
  }
  a.insert(begin(a), a[0]);
  b.push_back(b.back());
  cout << count_between_two_sequences(a, b) << '\n';
  return 0;
}
