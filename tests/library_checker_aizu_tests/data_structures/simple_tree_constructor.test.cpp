#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "point_set_range_composite"
#include "../template.hpp"
#include "../../../library/data_structures/seg_tree.hpp"
const int mod = 998'244'353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<array<int, 2>> init(n);
  for (int i = 0; i < n; i++)
    cin >> init[i][0] >> init[i][1];
  tree st(init, {1, 0},
    [&](const array<int, 2>& le,
      const array<int, 2>& ri) -> array<int, 2> {
      return {int(1LL * le[0] * ri[0] % mod),
        int((1LL * ri[0] * le[1] + ri[1]) % mod)};
    });
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int pos, c, d;
      cin >> pos >> c >> d;
      st.update(pos, {c, d});
    } else {
      int le, ri, x;
      cin >> le >> ri >> x;
      assert(st.query(le, le) == st.unit);
      assert(st.query(ri, ri) == st.unit);
      auto [slope, y_int] = st.query(le, ri);
      cout << (1LL * slope * x + y_int) % mod << '\n';
    }
  }
  return 0;
}
