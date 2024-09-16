#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"
#include "../template.hpp"

#include "../../../library/data_structures/seg_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  tree st(n, INT_MAX,
          [&](int x, int y) -> int { return min(x, y); });
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int pos, new_val;
      cin >> pos >> new_val;
      st.update(pos, new_val);
    } else {
      int le, ri;
      cin >> le >> ri;
      ri++;
      cout << st.query(le, ri) << '\n';
    }
  }
  return 0;
}
