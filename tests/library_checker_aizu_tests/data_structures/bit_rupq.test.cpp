#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/bit_uncommon/rupq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  bit_rupq bit_i_1(n);
  bit_rupq bit_i_2(vector<ll>(n, 50));
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int l, r, x;
      cin >> l >> r >> x;
      l--;
      bit_i_1.update(l, r, x);
      bit_i_2.update(l, r, x);
      // test degenerate updates
      bit_i_1.update(l, l, x);
      bit_i_1.update(r, r, x);
      bit_i_2.update(l, l, x);
      bit_i_2.update(r, r, x);
    } else {
      int idx;
      cin >> idx;
      idx--;
      ll res = bit_i_1.get_index(idx);
      assert(res == bit_i_2.get_index(idx) - 50);
      cout << res << '\n';
    }
  }
  return 0;
}
