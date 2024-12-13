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
  while (q--) {
    int u, v, k;
    cin >> u >> v >> k;
    int dist_in_edges = tl.dist_edges(u, v);
    assert(dist_in_edges == lc.dist_edges(u, v));
    cout << tl.kth_path(u, v, k) << '\n';
    {
      int w = rnd(0, n - 1);
      assert(lc.on_path(u, v, w) ==
             (lc.dist_edges(u, w) + lc.dist_edges(w, v) ==
              lc.dist_edges(u, v)));
    }
    if (u != v) {
      assert(tl.kth_path(u, v, 1) == lc.next_on_path(u, v));
      assert(tl.kth_path(u, v, dist_in_edges - 1) == lc.next_on_path(v, u));
    }
  }
}
