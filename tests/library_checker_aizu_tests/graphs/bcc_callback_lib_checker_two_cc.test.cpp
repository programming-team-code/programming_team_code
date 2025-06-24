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
  for (int i = 0; i < n; i++) adj[i] += i;
  vector<array<int, 2>> edges(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u] += v;
    adj[v] += u;
    if (u > v) swap(u, v);
    edges[i] = {u, v};
  }
  UF uf(n);
  ranges::sort(edges);
  for (int i = 1; i < m; i++)
    if (edges[i - 1] == edges[i])
      uf.join(edges[i][0], edges[i][1]);
  bcc_callback(adj, [&](const vi& nodes) {
    assert(sz(nodes) >= 2);
    if (sz(nodes) == 2) return;
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
