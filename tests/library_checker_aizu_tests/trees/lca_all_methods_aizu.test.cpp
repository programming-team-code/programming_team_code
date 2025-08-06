#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"
#include "../template.hpp"
#include "../../../library/monotonic_stack/monotonic_stack.hpp"
#include "../../../library/trees/tree_lift.hpp"
#include "../../../library/trees/linear_lca.hpp"
#include "../../../library/trees/lca_rmq.hpp"
#include "../compress_tree_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    adj[i].resize(k);
    for (int& child : adj[i]) cin >> child;
  }
  tree_lift tl(adj);
  LCA lc(adj);
  linear_lca lin_lca(adj);
  compress_tree_asserts(adj, lc);
  for (int i = 0; i < n; i++) {
    assert(tl.lca(i, i) == i);
    assert(lc.lca(i, i) == i);
    assert(lin_lca.lca(i, i) == i);
    assert(lc.tin[lc.rmq.dp[0][i]] == i &&
      lc.rmq.dp[0][lc.tin[i]] == i);
  }
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    int lca = tl.lca(u, v);
    assert(lca == lc.lca(u, v));
    assert(lca == lin_lca.lca(u, v));
    assert((lca == u) == lc.in_subtree(u, v));
    assert((lca == v) == lc.in_subtree(v, u));
    cout << lca << '\n';
  }
}
