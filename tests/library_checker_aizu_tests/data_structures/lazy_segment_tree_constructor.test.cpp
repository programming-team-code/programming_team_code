#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/lazy_seg_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    // test empty seg tree
    seg_tree st{vi()};
    st.update(0, 0, 1);
    ll res = st.query(0, 0);
    assert(res == 0);
  }
  int n, q;
  cin >> n >> q;
  vi arr(n);
  rep(i, 0, n) cin >> arr[i];
  seg_tree st(arr);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int idx;
      ll x;
      cin >> idx >> x;
      st.update(idx, idx + 1, x);
      st.update(idx, idx, 1);
    } else {
      assert(type == 1);
      int l, r;
      cin >> l >> r;
      cout << st.query(l, r) << '\n';
      {
        ll res = st.query(l, l);
        assert(res == 0);
      }
      {
        ll res = st.query(r, r);
        assert(res == 0);
      }
    }
  }
  return 0;
}
