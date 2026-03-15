#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/seg_tree.hpp"
const int mod = 998'244'353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  const array<int, 2> unit = {1, 0};
  tree st(n, unit,
    [&](const array<int, 2>& l,
      const array<int, 2>& r) -> array<int, 2> {
      return {int(1LL * l[0] * r[0] % mod),
        int((1LL * r[0] * l[1] + r[1]) % mod)};
    });
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    st.update(i, {a, b});
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int pos, c, d;
      cin >> pos >> c >> d;
      st.update(pos, {c, d});
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      assert(st.query(l, l) == st.unit);
      assert(st.query(r, r) == st.unit);
      array<int, 2> res = st.query(l, r);
      {
        array<int, 2> walk_res = {1, 0};
        int idx = -1;
        st.max_right(l, r,
          [&](int m,
            const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            idx = m;
            return 1;
          });
        assert(res == walk_res);
        assert(idx == r);
      }
      {
        array<int, 2> walk_res = unit;
        int idx = -1;
        st.max_right(l, r,
          [&](int m,
            const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            idx = m;
            return 0;
          });
        assert(walk_res == st.query(l, l + 1));
        assert(idx == l + 1);
      }
      {
        array<int, 2> walk_res = unit;
        int idx = -1;
        st.min_left(l, r,
          [&](int m,
            const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            idx = m;
            return 1;
          });
        assert(walk_res == res);
        assert(idx == l);
      }
      {
        array<int, 2> walk_res = unit;
        int idx = -1;
        st.min_left(l, r,
          [&](int m,
            const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            idx = m;
            return 0;
          });
        assert(walk_res == st.query(r - 1, r));
        assert(idx == r - 1);
      }
      cout << (1LL * res[0] * x + res[1]) % mod << '\n';
    }
  }
  return 0;
}
