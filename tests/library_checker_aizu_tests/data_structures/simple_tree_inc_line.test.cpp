#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "../template.hpp"
#include "../../../library/data_structures/seg_tree_inc.hpp"
const int mod = 998'244'353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<array<int, 2>> init(n);
  for (int i = 0; i < n; i++)
    cin >> init[i][0] >> init[i][1];
  tree_inc st(n, array<int, 2>{1, 0},
    [&](const array<int, 2>& l,
      const array<int, 2>& r) -> array<int, 2> {
      return {int(1LL * l[0] * r[0] % mod),
        int((1LL * r[0] * l[1] + r[1]) % mod)};
    });
  for (int i = 0; i < n; i++) st.update(i, init[i]);
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
      auto [slope, y_int] = st.query(l, r - 1);
      cout << (1LL * slope * x + y_int) % mod << '\n';
    }
  }
  return 0;
}
