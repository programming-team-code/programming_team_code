#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "static_range_mode_query"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon/mode_query.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) { cin >> a[i]; }
  vector<int> comp(a);
  sort(begin(comp), end(comp));
  comp.erase(unique(begin(comp), end(comp)), end(comp));
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
    int le, ri;
    cin >> le >> ri;
    auto [mode, cnt] = mq.query(le, ri);
    cout << comp[mode] << " " << cnt << '\n';
  }
  return 0;
}
