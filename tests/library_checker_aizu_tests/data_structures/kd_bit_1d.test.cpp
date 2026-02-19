#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/bit_uncommon/kd_bit.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  KD_BIT<1> bit1(n);
  KD_BIT<2> bit2(1, n);
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    bit1.update(i, val);
    bit2.update(0, i, val);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int p, x;
      cin >> p >> x;
      bit1.update(p, x);
      bit2.update(0, p, x);
    } else {
      int l, r;
      cin >> l >> r;
      ll res = bit1.query(l, r);
      assert(res == bit2.query(0, 1, l, r));
      cout << res << '\n';
    }
  }
  return 0;
}
