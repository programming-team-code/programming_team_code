#define PROBLEM \
  "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"
#include "../../../library/trees/linear_kth_path.hpp"
#include "../../../library/trees/lca_rmq/lca_rmq.hpp"
#include "../compress_tree_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  linear_kth_path lin_kth_path(adj);
  LCA lc(adj);
  compress_tree_asserts(adj, lc);
  while (q--) {
    int u, v, k;
    cin >> u >> v >> k;
    cout << lin_kth_path.kth_path(u, v, k) << '\n';
  }
}
