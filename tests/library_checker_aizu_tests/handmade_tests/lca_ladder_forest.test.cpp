#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/dsu/dsu_restorable.hpp"
#include "../../../library/monotonic_stack/monotonic_stack.hpp"
#include "../../../library/trees/tree_lift/tree_lift.hpp"
#include "../../../library/trees/lca_rmq/lca_rmq.hpp"
#include "../../../library/trees/ladder_decomposition/ladder_decomposition.hpp"
#include "../../../library/trees/ladder_decomposition/linear_kth_par.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 1; n <= 100; n++) {
    vector<vector<int>> adj(n);
    dsu_restorable dsu(n);
    for (int i = 0; i < n - 2; i++) {
      int u = rnd<int>(0, n - 1);
      int v = rnd<int>(0, n - 1);
      if (u == v) continue;
      if (dsu.join(u, v)) {
        adj[u].push_back(v);
        adj[v].push_back(u);
      }
    }
    tree_lift tl(adj);
    LCA lc(adj);
    ladder lad(adj);
    for (int i = 0; i < 100; i++) {
      int u = rnd<int>(0, n - 1);
      int v = rnd<int>(0, n - 1);
      if (u == v || !dsu.same_set(u, v)) continue;
      auto lca_1 = tl.lca(u, v);
      auto lca_2 = lc.lca(u, v);
      assert(lca_1 == lca_2);
      assert(tl.dist_edges(u, v) == lc.dist_edges(u, v));
      assert(
        tl.kth_path(u, v, 1) == lc.next_on_path(u, v));
      if (tl.t[u].d > tl.t[v].d) swap(u, v);
      auto res = tl.kth_par(v, tl.t[v].d - tl.t[u].d);
      assert(res == lad.kth_par(v, tl.t[v].d - tl.t[u].d));
      assert((u == res) == lc.in_subtree(u, v));
    }
  }
  cout << "Hello World\n";
  return 0;
}
