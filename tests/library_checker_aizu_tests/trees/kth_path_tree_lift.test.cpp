#define PROBLEM \
  "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/trees/tree_lift/tree_lift.hpp"
#include "../../../library/trees/lca_rmq/lca_rmq.hpp"
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
  tree_lift tl(adj);
  LCA lc(adj);
  auto kth_path = [&](int u, int v, int k) -> int {
    int lca_d = lc.d[lc.lca(u, v)];
    int u_lca = lc.d[u] - lca_d;
    int v_lca = lc.d[v] - lca_d;
    if (k <= u_lca) return tl.kth_par(u, k);
    if (k <= u_lca + v_lca)
      return tl.kth_par(v, u_lca + v_lca - k);
    return -1;
  };
  while (q--) {
    int u, v, k;
    cin >> u >> v >> k;
    int dist_in_edges = tl.dist(u, v);
    assert(dist_in_edges == lc.dist(u, v));
    cout << kth_path(u, v, k) << '\n';
    {
      int w = rnd(0, n - 1);
      assert(lc.on_path(u, v, w) ==
        (lc.dist(u, w) + lc.dist(w, v) == lc.dist(u, v)));
    }
    if (u != v) {
      assert(kth_path(u, v, 1) == lc.next_on_path(u, v));
      assert(kth_path(u, v, dist_in_edges - 1) ==
        lc.next_on_path(v, u));
    }
  }
}
