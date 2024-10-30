#define PROBLEM \
  "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"
#include "../cd_asserts.hpp"
#include "../../../library/trees/centroid_decomp.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cd_asserts(adj);
  vector<int> cent_par(n), cent_depth(n);
  vector<vector<int>> c_depth(n);
  centroid(adj,
    [&](const vector<vi>& cent_adj, int cent,
      int par_cent) {
      cent_par[cent] = par_cent;
      if (par_cent != -1)
        cent_depth[cent] = 1 + cent_depth[par_cent];
      auto dfs = [&](auto&& self, int v, int p,
                   int d) -> void {
        c_depth[v].push_back(d);
        for (int ch : cent_adj[v]) {
          if (ch == p) continue;
          self(self, ch, v, d + 1);
        }
      };
      dfs(dfs, cent, -1, 0);
    });
  vector<vector<array<int, 3>>> queries(n);
  vector<int> res(q);
  for (int q_idx = 0; q_idx < q; q_idx++) {
    int s, t, i;
    cin >> s >> t >> i;
    int u = s, v = t;
    while (u != v)
      if (cent_depth[u] > cent_depth[v]) u = cent_par[u];
      else v = cent_par[v];
    int lca_d = cent_depth[u];
    if (i > c_depth[s][lca_d] + c_depth[t][lca_d])
      res[q_idx] = -1;
    else if (i < c_depth[s][lca_d]) {
      queries[s].push_back({lca_d, i, q_idx});
    } else {
      queries[t].push_back({lca_d,
        c_depth[s][lca_d] + c_depth[t][lca_d] - i, q_idx});
    }
  }
  for (int i = 0; i < n; i++)
    sort(begin(queries[i]), end(queries[i]));
  vector<int> pos(n);
  centroid(adj,
    [&](const vector<vi>& cent_adj, int cent, int) {
      vector<int> st;
      auto dfs = [&](auto&& self, int v, int p) -> void {
        st.push_back(v);
        while (pos[v] < sz(queries[v]) &&
          queries[v][pos[v]][0] == cent_depth[cent]) {
          auto [_, k, q_idx] = queries[v][pos[v]];
          res[q_idx] = st[sz(st) - 1 - k];
          pos[v]++;
        }
        for (int ch : cent_adj[v]) {
          if (ch == p) continue;
          self(self, ch, v);
        }
        st.pop_back();
      };
      dfs(dfs, cent, -1);
    });
  for (int i = 0; i < q; i++) cout << res[i] << '\n';
}
