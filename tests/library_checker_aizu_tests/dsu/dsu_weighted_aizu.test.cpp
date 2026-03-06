#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B"
#include "../template.hpp"
#include "../../../library/dsu/dsu_weighted.hpp"
#include "../../../library/dsu/dsu.hpp"
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
      dsu_w.join(u, v, w);
      dsu.join(u, v);
      assert(dsu.size(u) == dsu_w.size(u));
      assert(dsu.size(v) == dsu_w.size(v));
    } else {
      ll curr_diff = dsu_w.diff(u, v);
      if (curr_diff == ll(1e18)) cout << "?\n";
      else cout << dsu_w.diff(u, v) << '\n';
      assert(dsu.size(u) == dsu_w.size(u));
      assert(dsu.size(v) == dsu_w.size(v));
    }
  }
  return 0;
}
