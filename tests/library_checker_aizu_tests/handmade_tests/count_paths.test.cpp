#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
//! @param adj unrooted, connected forest
//! @param k number of edges
//! @returns array `num_paths` where `num_paths[i]` =
//! number of paths with k edges where node `i` is on the
//! path. 0-based nodes.
//! @time O(n log n)
//! @space this function allocates/returns various vectors
//! which are all O(n)
vector<ll> count_paths_per_node(const vector<vi>& adj,
  int k) {
  vector<ll> num_paths(sz(adj));
  centroid(adj,
    [&](const vector<vi>& cd_adj, int cent, int) {
      vector pre_d{1}, cur_d{0};
      auto dfs = [&](auto&& self, int u, int p,
                   int d) -> ll {
        if (d > k) return 0LL;
        if (sz(cur_d) <= d) cur_d.push_back(0);
        cur_d[d]++;
        ll cnt = 0;
        if (k - d < sz(pre_d)) cnt += pre_d[k - d];
        for (int c : cd_adj[u])
          if (c != p) cnt += self(self, c, u, d + 1);
        num_paths[u] += cnt;
        return cnt;
      };
      auto dfs_child = [&](int child) -> ll {
        ll cnt = dfs(dfs, child, cent, 1);
        pre_d.resize(sz(cur_d));
        for (int i = 1; i < sz(cur_d) && cur_d[i]; i++)
          pre_d[i] += cur_d[i], cur_d[i] = 0;
        return cnt;
      };
      for (int child : cd_adj[cent])
        num_paths[cent] += dfs_child(child);
      pre_d = cur_d = {0};
      for (int child : cd_adj[cent] | views::reverse)
        dfs_child(child);
    });
  return num_paths;
}
#include "../../../library/trees/lca_rmq.hpp"
#include "../cd_asserts.hpp"
vector<vector<ll>> naive(const vector<vi>& adj) {
  LCA lc(adj);
  int n = sz(adj);
  vector<vector<ll>> cnts_naive(n + 1, vector<ll>(n, 0));
  for (int u = 0; u < n; u++) {
    for (int v = u; v < n; v++) {
      int path_length_edges = lc.dist(u, v);
      for (int node = u; node != v;
        node = lc.next_on_path(node, v))
        cnts_naive[path_length_edges][node]++;
      cnts_naive[path_length_edges][v]++;
    }
  }
  return cnts_naive;
}
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
  for (int n = 1; n <= 100; n++) {
    vector<vi> adj(n);
    for (int i = 1; i < n; i++) {
      int par = rnd<int>(0, i - 1);
      adj[par].push_back(i);
      adj[i].push_back(par);
    }
    cd_asserts(adj);
    vector<vector<ll>> cnts_naive = naive(adj);
    for (int k = 1; k <= n; k++)
      assert(
        count_paths_per_node(adj, k) == cnts_naive[k]);
    vector<ll> num_paths_len = count_paths_per_length(adj);
    for (int k = 1; k < n; k++) {
      vector<ll> count_paths =
        count_paths_per_node(adj, k);
      ll total_paths = accumulate(begin(count_paths),
        end(count_paths), 0LL);
      assert(total_paths % (k + 1) == 0);
      total_paths /= k + 1;
      assert(num_paths_len[k] == total_paths);
    }
  }
  cout << "Hello World\n";
  return 0;
}
