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
    assert(sz(nodes) >= 2);
    if (sz(nodes) == 2)
      bridges.emplace_back(min(nodes[0], nodes[1]),
        max(nodes[0], nodes[1]));
  });
  ranges::sort(bridges);
  for (auto [u, v] : bridges)
    cout << u << ' ' << v << '\n';
  return 0;
}
