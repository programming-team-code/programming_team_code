#define PROBLEM                                         \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/" \
  "DSL/all/DSL_2_G"
#include "../template.hpp"

#include "../../../library/data_structures/lazy_seg_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    // test empty seg tree
    seg_tree st(0);
    st.update(0, 0, 1);
    int64_t res = st.query(0, 0);
    assert(res == 0);
  }
  int n, q;
  cin >> n >> q;
  seg_tree st(n);
  while (q--) {
    int type, l, r;
    cin >> type >> l >> r;
    l--;
    if (type == 0) {
      int64_t x;
      cin >> x;
      st.update(l, r, x);
      st.update(l, l, 1);
      st.update(r, r, 1);
    } else {
      assert(type == 1);
      cout << st.query(l, r) << '\n';
      {
        int64_t res = st.query(l, l);
        assert(res == 0);
      }
      {
        int64_t res = st.query(r, r);
        assert(res == 0);
      }
    }
  }
  return 0;
}
