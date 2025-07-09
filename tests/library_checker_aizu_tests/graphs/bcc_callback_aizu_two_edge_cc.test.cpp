#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B"
#include "../template.hpp"
#include "../../../library/graphs/bridges_cuts/bcc_callback.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<basic_string<int>> adj(n);
  for (int i = 0; i < n; i++) adj[i] += i;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u] += v;
    adj[v] += u;
  }
  vector<pii> bridges;
  bcc_callback(adj, [&](const vi& nodes) {
    if (sz(nodes) == 2) {
      pii bridge(nodes[0], nodes[1]);
      if (bridge.first > bridge.second)
        swap(bridge.first, bridge.second);
      bridges.push_back(bridge);
      // nodes[0] <=> nodes[1] is a bridge
      return;
    }
  });
  ranges::sort(bridges);
  for (auto [u, v] : bridges)
    cout << u << ' ' << v << '\n';
  return 0;
}
