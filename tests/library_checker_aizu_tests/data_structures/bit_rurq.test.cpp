#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/bit_uncommon/rurq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  bit_rurq bit(n);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int l, r, x;
      cin >> l >> r >> x;
      l--;
      bit.update(l, r, x);
      // test degenerate update
      bit.update(l, l, x);
      bit.update(r, r, x);
    } else {
      int l, r;
      cin >> l >> r;
      l--;
      cout << bit.query(l, r) << '\n';
    }
  }
  return 0;
}
