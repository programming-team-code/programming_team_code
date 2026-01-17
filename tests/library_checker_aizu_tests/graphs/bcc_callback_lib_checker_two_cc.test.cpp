#define PROBLEM \
  "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../template.hpp"
#include "../../../library/graphs/bcc_callback.hpp"
#include "../../../library/data_structures/dsu/dsu.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vi> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  DSU dsu(n);
  vector<bool> seen(n);
  bcc(adj, [&](const vi& nodes) {
    int count_edges = 0;
    rep(i, 0, sz(nodes) - 1) {
      seen[nodes[i]] = 1;
      count_edges += ranges::count_if(adj[nodes[i]],
        [&](int v) -> bool { return !seen[v]; });
    }
    if (count_edges == 1) {
      assert(sz(nodes) == 2);
      // nodes[0] <=> nodes[1] is a bridge
      return;
    }
    for (int v : nodes) dsu.join(v, nodes[0]);
  });
  vector<vi> two_edge_ccs(n);
  rep(i, 0, n) two_edge_ccs[dsu.f(i)].push_back(i);
  int cnt_ccs = 0;
  rep(i, 0, n) cnt_ccs += (!empty(two_edge_ccs[i]));
  cout << cnt_ccs << '\n';
  rep(i, 0, n) {
    if (!empty(two_edge_ccs[i])) {
      cout << sz(two_edge_ccs[i]) << ' ';
      for (int v : two_edge_ccs[i]) cout << v << ' ';
      cout << '\n';
    }
  }
  return 0;
}
