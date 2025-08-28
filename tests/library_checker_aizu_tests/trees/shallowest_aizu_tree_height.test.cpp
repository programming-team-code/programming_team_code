#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_B"
#include "../template.hpp"
#include "../../../library/trees/shallowest_decomp_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  map<pair<int, int>, int> weight;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    weight[{u, v}] = w;
    weight[{v, u}] = w;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> res(n);
  shallowest(adj, [&](int cent) {
    int lowest = 0;
    int curr_lowest = 0;
    auto dfs = [&](auto&& self, int v, int p,
                 int height) -> void {
      res[v] = max(res[v], height + lowest);
      res[cent] = max(res[cent], height);
      curr_lowest = max(curr_lowest, height);
      for (int u : adj[v])
        if (u != p)
          self(self, u, v, height + weight[{u, v}]);
    };
    for (int v : adj[cent]) {
      curr_lowest = 0;
      dfs(dfs, v, cent, weight[{v, cent}]);
      lowest = max(lowest, curr_lowest);
    }
    lowest = 0;
    for (int v : adj[cent] | views::reverse) {
      curr_lowest = 0;
      dfs(dfs, v, cent, weight[{v, cent}]);
      lowest = max(lowest, curr_lowest);
    }
  });
  for (int i = 0; i < n; i++) cout << res[i] << '\n';
}
