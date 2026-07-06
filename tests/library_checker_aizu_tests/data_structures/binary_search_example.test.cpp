#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/DSL_3_A"
#include "../template.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    ll lo = -5, hi = 5;
#include "../../../library/contest/binary_search.hpp"
    assert(res == 0);
  }
  int n, s;
  cin >> n >> s;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  vi pref_sum(a);
  rep(i, 1, n) pref_sum[i] += pref_sum[i - 1];
  auto sum = [&](int l, int r) -> int { //[l,r]
    int res = pref_sum[r];
    if (l) res -= pref_sum[l - 1];
    return res;
  };
  if (sum(0, n - 1) < s) {
    cout << 0 << '\n';
    return 0;
  }
  int res = n;
  rep(i, 0, n) {
    if (sum(i, n - 1) < s) break;
    int cur = *ranges::partition_point(views::iota(i, n),
      [&](int x) -> bool { return sum(i, x) < s; });
    res = min(res, cur - i + 1);
  }
  cout << res << '\n';
  return 0;
}
