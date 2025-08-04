#define PROBLEM \
  "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"
#include "../../../library/trees/linear_lca.hpp"
#include "../../../library/trees/ladder_decomposition/linear_kth_par.hpp"
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
  linear_lca lin_lca(adj);
  linear_kth_par lin_kth_par(adj);
  LCA lc(adj);
  compress_tree_asserts(adj, lc);
  while (q--) {
    int u, v, k;
    cin >> u >> v >> k;
    int lca_d = lin_kth_par.t[lin_lca.lca(u, v)].d;
    int u_lca = lin_kth_par.t[u].d - lca_d;
    int v_lca = lin_kth_par.t[v].d - lca_d;
    if (k <= u_lca) cout << lin_kth_par.kth_par(u, k) << '\n';
    else if (k <= u_lca + v_lca)
      cout << lin_kth_par.kth_par(v, u_lca + v_lca - k) << '\n';
    else cout << -1 << '\n';
  }
}
