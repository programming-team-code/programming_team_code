#define PROBLEM \
  "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../template.hpp"
#include "../../../library/graphs/bridges_cuts/bcc_callback.hpp"
#include "../../../kactl/content/data-structures/UnionFind.h"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<basic_string<int>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u] += v;
    adj[v] += u;
  }
  UF uf(n);
  vector<bool> seen(n);
  bcc_callback(adj, [&](const vi& nodes) {
    int count_edges = 0;
    rep(i, 0, sz(nodes) - 1) {
      seen[nodes[i]] = 1;
      for (int v : adj[nodes[i]])
        if (!seen[v]) {
          // edge nodes[i] <=> v is in current BCC
          count_edges++;
        }
    }
    if (count_edges == 1) {
      assert(sz(nodes) == 2);
      // nodes[0] <=> nodes[1] is a bridge
      return;
    }
    for (int v : nodes) uf.join(v, nodes[0]);
  });
  vector<basic_string<int>> two_edge_ccs(n);
  rep(i, 0, n) two_edge_ccs[uf.find(i)] += i;
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
