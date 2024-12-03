#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"
#include "../template.hpp"
#include "../../../library/data_structures/seg_tree_inc.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  tree_inc st(vector<int>(n, INT_MAX), ranges::min);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int pos, new_val;
      cin >> pos >> new_val;
      st.update(pos, new_val);
    } else {
      int l, r;
      cin >> l >> r;
      cout << st.query(l, r) << '\n';
    }
  }
  return 0;
}
