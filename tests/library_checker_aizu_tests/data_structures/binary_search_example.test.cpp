#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/DSL_3_A"
#include "../template.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    ll lo, hi;
#include "../../../library/contest/binary_search.hpp"
  }
  int n, s;
  cin >> n >> s;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<int> pref_sum(a);
  for (int i = 1; i < n; i++)
    pref_sum[i] += pref_sum[i - 1];
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
  for (int i = 0; i < n; i++) {
    if (sum(i, n - 1) < s) break;
    int curr = *ranges::partition_point(views::iota(i, n),
      [&](int x) -> bool { return sum(i, x) < s; });
    res = min(res, curr - i + 1);
  }
  cout << res << '\n';
  return 0;
}
