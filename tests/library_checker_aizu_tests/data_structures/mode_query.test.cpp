#define PROBLEM "https://judge.yosupo.jp/problem/static_range_mode_query"
// it TLE's in debug mode currently :(
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/data_structures/uncommon/mode_query.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> comp(a);
  sort(begin(comp), end(comp));
  comp.erase(unique(begin(comp), end(comp)), end(comp));
  for (int& val : a) {
    val = lower_bound(begin(comp), end(comp), val) - begin(comp);
  }
  mode_query mq(a);
  while (q--) {
    int le, ri;
    cin >> le >> ri;
    auto [mode, cnt] = mq.query(le, ri);
    cout << comp[mode] << " " << cnt << '\n';
  }
  return 0;
}
