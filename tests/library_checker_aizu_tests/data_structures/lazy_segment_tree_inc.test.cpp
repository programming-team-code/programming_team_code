#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G"
#include "../template.hpp"
#include "../../../library/data_structures/lazy_seg_tree_inc.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  seg_tree_inc st(n);
  while (q--) {
    int type, l, r;
    cin >> type >> l >> r;
    l--, r--;
    if (type == 0) {
      int64_t x;
      cin >> x;
      st.update(l, r, x);
    } else {
      cout << st.query(l, r) << '\n';
    }
  }
  return 0;
}
