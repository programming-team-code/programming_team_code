#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../../../library/data_structures/uncommon/disjoint_rmq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  disjoint_rmq dis_rmq(a, ranges::min);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << dis_rmq.query(l, r) << '\n';
  }
}
