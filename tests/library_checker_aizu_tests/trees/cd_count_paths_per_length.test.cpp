#define PROBLEM \
  "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../template.hpp"
#include "../cd_asserts.hpp"
#include "../../../kactl/content/numerical/FastFourierTransform.h"
//! @param adj unrooted, connected forest
//! @returns array `num_paths` where `num_paths[i]` = # of
//! paths in tree with `i` edges. `num_paths[1]` = # edges
//! @time O(n log^2 n)
//! @space this function allocates/returns various vectors
//! which are each O(n)
vector<ll> count_paths_per_length(vector<vi> adj) {
  vector<ll> num_paths(sz(adj));
  centroid(adj, [&](int cent, int) {
    vector<vector<double>> child_depths;
    for (int v : adj[cent]) {
      child_depths.emplace_back(1, 0.0);
      for (queue<pii> q({{v, cent}}); !empty(q);) {
        child_depths.back().push_back(sz(q));
        queue<pii> new_q;
        while (!empty(q)) {
          auto [u, p] = q.front();
          q.pop();
          for (int w : adj[u]) {
            if (w == p) continue;
            new_q.push({w, u});
          }
        }
        swap(q, new_q);
      }
    }
    sort(all(child_depths),
      [&](auto& x, auto& y) { return sz(x) < sz(y); });
    vector total_depth(1, 1.0);
    for (auto& cnt_depth : child_depths) {
      auto prod = conv(total_depth, cnt_depth);
      rep(i, 1, sz(prod)) num_paths[i] += llround(prod[i]);
      total_depth.resize(sz(cnt_depth));
      rep(i, 1, sz(cnt_depth)) total_depth[i] +=
        cnt_depth[i];
    }
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
  cd_asserts(adj);
  vector<ll> cnt_len = count_paths_per_length(adj);
  for (int i = 1; i < n; i++) cout << cnt_len[i] << " ";
  cout << '\n';
  return 0;
}
