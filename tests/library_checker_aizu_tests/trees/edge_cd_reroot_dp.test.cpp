#define PROBLEM \
  "https://judge.yosupo.jp/problem/tree_path_composite_sum"
#include "../template.hpp"
#include "../edge_cd_asserts.hpp"
#include "../../../library/trees/edge_cd.hpp"
#include "../../../library/math/mod_int.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<mint> res(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    res[i] = a[i];
  }
  vector<basic_string<int>> adj(n);
  vector<mint> b(n - 1), c(n - 1);
  vector<pair<int, int>> par(n, {-1, -1});
  vector<vector<int>> base_adj(n);
  {
    vector<vector<pair<int, int>>> adj_with_id(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v >> b[i].x >> c[i].x;
      adj[u].push_back(v);
      adj[v].push_back(u);
      base_adj[u].push_back(v);
      base_adj[v].push_back(u);
      adj_with_id[u].emplace_back(v, i);
      adj_with_id[v].emplace_back(u, i);
      res[u] = res[u] + b[i] * a[v] + c[i];
      res[v] = res[v] + b[i] * a[u] + c[i];
    }
    auto dfs = [&](auto&& self, int u) -> void {
      for (auto [v, e_id] : adj_with_id[u])
        if (v != par[u].first)
          par[v] = {u, e_id}, self(self, v);
    };
    dfs(dfs, 0);
  }
  auto edge_id = [&](int u, int v) -> int {
    bool u_low = (par[u].first == v);
    bool v_low = (par[v].first == u);
    assert(u_low ^ v_low);
    return u_low ? par[u].second : par[v].second;
  };
  { edge_cd(base_adj, edge_cd_asserts); }
  edge_cd(adj,
    [&](const vector<basic_string<int>>& cd_adj, int cent,
      int split) -> void {
      array<vector<array<mint, 3>>, 2> all_backwards;
      array<mint, 2> sum_forward = {0, 0};
      array<int, 2> cnt_nodes = {0, 0};
      auto dfs = [&](auto&& self, int u, int p,
                   array<mint, 2> forwards,
                   array<mint, 2> backwards,
                   int side) -> void {
        all_backwards[side].push_back(
          {u, backwards[0], backwards[1]});
        sum_forward[side] = sum_forward[side] +
          forwards[0] * a[u] + forwards[1];
        cnt_nodes[side]++;
        for (int v : cd_adj[u]) {
          if (v == p) continue;
          int e_id = edge_id(u, v);
          // f(x) = ax+b
          // g(x) = cx+d
          // f(g(x)) = a(cx+d)+b = acx+ad+b
          array<mint, 2> curr_forw = {
            forwards[0] * b[e_id],
            forwards[0] * c[e_id] + forwards[1]};
          array<mint, 2> curr_backw = {
            backwards[0] * b[e_id],
            backwards[1] * b[e_id] + c[e_id]};
          self(self, v, u, curr_forw, curr_backw, side);
        }
      };
      for (int i = 0; i < sz(cd_adj[cent]); i++) {
        int e_id = edge_id(cent, cd_adj[cent][i]);
        dfs(dfs, cd_adj[cent][i], cent, {b[e_id], c[e_id]},
          {b[e_id], c[e_id]}, i < split);
      }
      for (int side = 0; side < 2; side++) {
        for (
          auto [u, curr_b, curr_c] : all_backwards[side]) {
          res[u.x] = res[u.x] +
            curr_b * sum_forward[!side] +
            curr_c * cnt_nodes[!side];
        }
      }
    });
  for (int i = 0; i < n; i++) cout << res[i].x << ' ';
  cout << '\n';
  return 0;
}
