#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/tree_path_composite_sum"
#include "../template.hpp"
#include "../edge_cd_asserts.hpp"
#include "../../../library/trees/edge_cd.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int64_t> res(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    res[i] = a[i];
  }
  vector<vector<int>> adj(n);
  vector<int> b(n - 1), c(n - 1);
  vector<pair<int, int>> par(n, {-1, -1});
  const int mod = 998'244'353;
  {
    vector<vector<pair<int, int>>> adj_with_id(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v >> b[i] >> c[i];
      adj[u].push_back(v);
      adj[v].push_back(u);
      adj_with_id[u].push_back({v, i});
      adj_with_id[v].push_back({u, i});
      res[u] += 1LL * b[i] * a[v] + c[i];
      res[u] %= mod;
      res[v] += 1LL * b[i] * a[u] + c[i];
      res[v] %= mod;
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
  { edge_cd(adj, edge_cd_asserts); }
  edge_cd(adj,
    [&](const vector<vector<int>>& cd_adj, int cent,
      int split) -> void {
      array<vector<array<int64_t, 3>>, 2> all_backwards;
      array<int64_t, 2> sum_forward = {0, 0},
                        cnt_nodes = {0, 0};
      auto dfs = [&](auto&& self, int u, int p,
                   array<int64_t, 2> forwards,
                   array<int64_t, 2> backwards,
                   int side) -> void {
        all_backwards[side].push_back(
          {u, backwards[0], backwards[1]});
        sum_forward[side] +=
          forwards[0] * a[u] + forwards[1];
        sum_forward[side] %= mod;
        cnt_nodes[side]++;
        for (int v : cd_adj[u]) {
          if (v == p) continue;
          int e_id = edge_id(u, v);
          // f(x) = ax+b
          // g(x) = cx+d
          // f(g(x)) = a(cx+d)+b = acx+ad+b
          array<int64_t, 2> curr_forw = {
            forwards[0] * b[e_id] % mod,
            (forwards[0] * c[e_id] + forwards[1]) % mod};
          array<int64_t, 2> curr_backw = {
            b[e_id] * backwards[0] % mod,
            (b[e_id] * backwards[1] + c[e_id]) % mod};
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
          res[u] += curr_b * sum_forward[!side] +
            cnt_nodes[!side] * curr_c;
          res[u] %= mod;
        }
      }
    });
  for (int i = 0; i < n; i++) cout << res[i] << ' ';
  cout << '\n';
  return 0;
}
