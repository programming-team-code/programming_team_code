#define PROBLEM \
  "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"
#include "../../../library/trees/ladder_decomposition/ladder_decomposition.hpp"
#include "../../../library/trees/ladder_decomposition/linear_kth_par.hpp"
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
  ladder ld(adj);
  assert(sz(ld.l_tbl) <= 2 * n - ld.d[0]);
  while (q--) {
    int u, v, k;
    cin >> u >> v >> k;
    int lca_d = ld.d[lca(ld.b_tbl, ld.d, u, v)];
    int u_lca = ld.d[u] - lca_d;
    int v_lca = ld.d[v] - lca_d;
    if (k > u_lca + v_lca) cout << -1 << '\n';
    else if (k <= u_lca) {
      int res = ld.kth_par(u, k);
      assert(res == jmp(ld.b_tbl, u, k));
      cout << res << '\n';
    } else {
      int res = ld.kth_par(v, u_lca + v_lca - k);
      assert(res == jmp(ld.b_tbl, v, u_lca + v_lca - k));
      cout << res << '\n';
    }
  }
}
