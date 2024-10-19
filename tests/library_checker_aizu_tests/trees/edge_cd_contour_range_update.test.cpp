#define PROBLEM \
  "https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree"
#include "../template.hpp"
#include "../edge_cd_asserts.hpp"
#include "../../../library/trees/edge_centroid_decomp_uncommon/contour_range_update.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int64_t> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  { edge_cd(adj, edge_cd_asserts); }
  contour_range_update cu(adj, a);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int u, le, ri, delta;
      cin >> u >> le >> ri >> delta;
      cu.update(u, le, le, delta);
      cu.update(u, le, ri, delta);
      cu.update(u, ri, ri, delta);
    } else {
      assert(type == 1);
      int u;
      cin >> u;
      cout << cu.query(u) << '\n';
    }
  }
  return 0;
}
