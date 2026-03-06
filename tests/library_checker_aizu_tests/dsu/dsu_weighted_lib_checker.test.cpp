#define PROBLEM \
  "https://judge.yosupo.jp/problem/unionfind_with_potential"
#include "../template.hpp"
#include "../../../library/dsu/dsu_weighted.hpp"
#include "../../../library/dsu/dsu.hpp"
const int mod = 998'244'353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  dsu_weighted dsu_w(n);
  DSU dsu(n);
  while (q--) {
    int type, u, v;
    cin >> type >> u >> v;
    if (type == 0) {
      int w;
      cin >> w;
      ll curr_diff = dsu_w.diff(u, v);
      if (curr_diff == 1e18) {
        assert(dsu_w.join(u, v, w));
        cout << 1 << '\n';
      } else
        cout << ((curr_diff % mod + mod) % mod == w)
             << '\n';
      dsu.join(u, v);
      assert(dsu.size(u) == dsu_w.size(u));
      assert(dsu.size(v) == dsu_w.size(v));
    } else {
      ll curr_diff = dsu_w.diff(u, v);
      if (curr_diff == 1e18) cout << -1 << '\n';
      else cout << (curr_diff % mod + mod) % mod << '\n';
      assert(dsu.size(u) == dsu_w.size(u));
      assert(dsu.size(v) == dsu_w.size(v));
    }
  }
  return 0;
}
