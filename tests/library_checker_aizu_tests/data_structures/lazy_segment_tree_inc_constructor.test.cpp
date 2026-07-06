#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/lazy_seg_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  seg_tree st(a);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int idx;
      ll x;
      cin >> idx >> x;
      st.update(idx, idx, x);
    } else {
      assert(type == 1);
      int l, r;
      cin >> l >> r;
      cout << st.query(l, r - 1) << '\n';
    }
  }
  return 0;
}
