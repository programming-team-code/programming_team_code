#define PROBLEM \
  "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../template.hpp"
#include "../../../kactl/content/numerical/FastFourierTransform.h"
#include "../../../library/trees/edge_cd.hpp"
//! @param adj unrooted, connected tree
//! @returns array `num_paths` where `num_paths[i]` = # of
//! paths in tree with `i` edges. `num_paths[1]` = # edges
//! @time O(n * logφ(n) * log2(n))
//! @space this function allocates/returns various vectors
//! which are each O(n)
vector<ll> count_paths_per_length(const vector<vi>& adj) {
  vector<ll> num_paths(sz(adj));
  if (sz(adj) >= 2) num_paths[1] = sz(adj) - 1;
  edge_cd(adj,
    [&](const vector<vi>& cd_adj, int cent, int split) {
      vector<vector<double>> cnt(2, vector<double>(1));
      auto dfs = [&](auto&& self, int u, int p, int d,
                   int side) -> void {
        if (sz(cnt[side]) == d) cnt[side].push_back(0.0);
        cnt[side][d]++;
        for (int c : cd_adj[u])
          if (c != p) self(self, c, u, 1 + d, side);
      };
      rep(i, 0, sz(cd_adj[cent]))
        dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
      vector<double> prod = conv(cnt[0], cnt[1]);
      rep(i, 0, sz(prod)) num_paths[i] += llround(prod[i]);
    });
  return num_paths;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<ll> cnt_len = count_paths_per_length(adj);
  for (int i = 1; i < n; i++) cout << cnt_len[i] << " ";
  cout << '\n';
  return 0;
}
