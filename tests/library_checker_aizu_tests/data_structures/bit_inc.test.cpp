#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/bit.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  BIT bit(n);
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    bit.update(i, val);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int p, x;
      cin >> p >> x;
      bit.update(p, x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << bit.query(l, r - 1) << '\n';
    }
  }
  return 0;
}
