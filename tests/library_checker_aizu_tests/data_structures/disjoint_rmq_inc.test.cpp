#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../../../library/data_structures/uncommon/disjoint_rmq_inc.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vi a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  disjoint_rmq_inc rmq(a,
    [](int x, int y) { return min(x, y); });
  while (q--) {
    int le, ri;
    cin >> le >> ri;
    cout << rmq.query(le, ri - 1) << '\n';
  }
}
