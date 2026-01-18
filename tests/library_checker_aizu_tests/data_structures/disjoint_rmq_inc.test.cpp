#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/disjoint_rmq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vi a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  disjoint_rmq rmq(a,
    [](int x, int y) { return min(x, y); });
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << rmq.query(l, r - 1) << '\n';
  }
}
