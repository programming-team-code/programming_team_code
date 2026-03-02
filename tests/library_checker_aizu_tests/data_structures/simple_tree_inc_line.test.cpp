#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/seg_tree.hpp"
const int mod = 998'244'353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<array<int, 2>> a(n);
  for (int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];
  tree st(a,
    [&](const array<int, 2>& l,
      const array<int, 2>& r) -> array<int, 2> {
      return {int(1LL * l[0] * r[0] % mod),
        int((1LL * r[0] * l[1] + r[1]) % mod)};
    });
  const array<int, 2> unit = {1, 0};
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
      r--;
      array<int, 2> res = st.query(l, r);
      {
        array<int, 2> walk_res = {1, 0};
        int idx = st.max_right(l, r,
          [&](const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            return 1;
          });
        assert(res == walk_res);
        assert(idx == r + 1);
      }
      {
        array<int, 2> walk_res = unit;
        int idx = st.max_right(l, r,
          [&](const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            return 0;
          });
        assert(walk_res == st.query(l, l));
        assert(idx == l);
      }
      {
        array<int, 2> walk_res = unit;
        int idx = st.min_left(l, r,
          [&](const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            return 1;
          });
        assert(walk_res == res);
        assert(idx == l - 1);
      }
      {
        array<int, 2> walk_res = unit;
        int idx = st.min_left(l, r,
          [&](const array<int, 2>& curr_line) -> bool {
            walk_res = curr_line;
            return 0;
          });
        assert(walk_res == st.query(r, r));
        assert(idx == r);
      }
      cout << (1LL * res[0] * x + res[1]) % mod << '\n';
    }
  }
  return 0;
}
