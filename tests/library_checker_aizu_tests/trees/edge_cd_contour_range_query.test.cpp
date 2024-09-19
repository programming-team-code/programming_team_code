#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"
#include "../template.hpp"
#include "../edge_cd_asserts.hpp"
#include "../../../library/trees/edge_centroid_decomp_uncommon/contour_range_query.hpp"
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
  contour_range_query<int64_t> cq(adj, a);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int u;
      int64_t delta;
      cin >> u >> delta;
      cq.update(u, delta);
    } else {
      assert(type == 1);
      int u, le, ri;
      cin >> u >> le >> ri;
      int64_t res = cq.query(u, le, le);
      assert(res == 0);
      res = cq.query(u, ri, ri);
      assert(res == 0);
      cout << cq.query(u, le, ri) << '\n';
    }
  }
  return 0;
}
