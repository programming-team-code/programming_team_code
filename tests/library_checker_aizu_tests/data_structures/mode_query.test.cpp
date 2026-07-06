#define PROBLEM \
  "https://judge.yosupo.jp/problem/static_range_mode_query"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/uncommon/mode_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  vi comp(a);
  ranges::sort(comp);
  comp.erase(begin(ranges::unique(comp)), end(comp));
  for (int& val : a) {
    int start = 0, end = sz(comp);
    while (start + 1 < end) {
      int mid = (start + end) / 2;
      if (comp[mid] <= val) start = mid;
      else end = mid;
    }
    assert(0 <= start && start < sz(comp) &&
           comp[start] == val);
    val = start;
  }
  mode_query mq(a);
  while (q--) {
    int l, r;
    cin >> l >> r;
    auto [mode, cnt] = mq.query(l, r);
    cout << comp[mode] << " " << cnt << '\n';
  }
  return 0;
}
