#define PROBLEM \
  "https://judge.yosupo.jp/problem/eulerian_trail_undirected"
#include "../template.hpp"
#include "../../../library/graphs/euler_walk.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> adj(n);
    vector<int> deg(n);
    int s = -1;
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      s = u;
      adj[u].emplace_back(v, i);
      adj[v].emplace_back(u, i);
      deg[u] ^= 1;
      deg[v] ^= 1;
    }
    if (ranges::count(deg, 1) > 2) {
      cout << "No" << '\n';
      continue;
    }
    auto it = ranges::find(deg, 1);
    if (it != end(deg)) s = it - begin(deg);
    else if (s == -1) s = 0;
    vector<pii> res = euler_walk(adj, m, s);
    if (ssize(res) != m + 1) {
      cout << "No" << '\n';
      continue;
    }
    cout << "Yes" << '\n';
    for (int i = 0; i < ssize(res); i++)
      cout << res[i].first << ' ';
    cout << '\n';
    for (int i = 1; i < ssize(res); i++)
      cout << res[i].second << ' ';
    cout << '\n';
  }
  return 0;
}
