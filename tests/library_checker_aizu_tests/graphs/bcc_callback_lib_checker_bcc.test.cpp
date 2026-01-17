#define PROBLEM \
  "https://judge.yosupo.jp/problem/biconnected_components"
#include "../template.hpp"
#include "../../../library/graphs/bcc_callback.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) adj[i].push_back(i);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<bool> vis(n, 0);
  vector<vector<int>> all_bccs;
  bcc(adj, [&](const vi& nodes) {
    assert(ssize(nodes) >= 2);
    for (int v : nodes) vis[v] = 1;
    all_bccs.push_back(nodes);
  });
  for (int i = 0; i < n; i++)
    if (!vis[i]) all_bccs.push_back({i});
  cout << ssize(all_bccs) << '\n';
  for (const vector<int>& other_nodes : all_bccs) {
    cout << ssize(other_nodes) << ' ';
    for (int v : other_nodes) cout << v << ' ';
    cout << '\n';
  }
  return 0;
}
