#define PROBLEM \
  "https://judge.yosupo.jp/problem/biconnected_components"
#include "../template.hpp"
#include "../../../library/graphs/bcc_callback.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vi> adj(n);
  rep(i, 0, n) adj[i].push_back(i);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<bool> vis(n, 0);
  vector<vi> all_bccs;
  bcc(adj, [&](const vi& nodes) {
    assert(sz(nodes) >= 2);
    for (int v : nodes) vis[v] = 1;
    all_bccs.push_back(nodes);
  });
  rep(i, 0, n) if (!vis[i]) all_bccs.push_back({i});
  cout << sz(all_bccs) << '\n';
  for (const vi& other_nodes : all_bccs) {
    cout << sz(other_nodes) << ' ';
    for (int v : other_nodes) cout << v << ' ';
    cout << '\n';
  }
  return 0;
}
