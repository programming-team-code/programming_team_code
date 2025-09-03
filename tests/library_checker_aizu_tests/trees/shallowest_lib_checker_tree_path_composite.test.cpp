#define PROBLEM \
  "https://judge.yosupo.jp/problem/tree_path_composite_sum"
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/trees/shallowest_decomp_tree.hpp"
#include "../../../library/math/mod_int.hpp"
using line = array<mint, 2>;
// returns f(g(x)) = f[0]*(g[0]*x+g[1]) + f[1]
line compose(line f, line g) {
  return {f[0] * g[0], f[1] + f[0] * g[1]};
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<mint> a(n);
  for (int i = 0; i < n; i++) cin >> a[i].x;
  vector<vector<int>> adj(n);
  vector<vector<line>> weight(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, b, c;
    cin >> u >> v >> b >> c;
    adj[u].push_back(v);
    adj[v].push_back(u);
    weight[u].push_back({b, c});
    weight[v].push_back({b, c});
  }
  vector<mint> res(n);
  for (int i = 0; i < n; i++) res[i] = a[i];
  shallowest(adj, [&](int cent) {
    assert(ssize(adj[cent]) == ssize(weight[cent]));
    mint total_sum_evaluated = 0;
    int total_cnt_nodes = 0;
    mint curr_sum_evaluated = 0;
    int curr_cnt_nodes = 0;
    auto dfs = [&](auto&& self, int v, int p,
                 line downwards, line upwards,
                 bool forwards) -> void {
      // f(x) + f(y) + f(z) = b*x+c + b*y+c + b*z+c =
      // b*(x+y+z) + c*3
      res[v] = res[v] + upwards[0] * total_sum_evaluated +
        upwards[1] * total_cnt_nodes;
      if (forwards) {
        res[v] =
          res[v] + upwards[0] * a[cent] + upwards[1];
        res[cent] =
          res[cent] + downwards[0] * a[v] + downwards[1];
      }
      curr_cnt_nodes++;
      curr_sum_evaluated = curr_sum_evaluated +
        downwards[0] * a[v] + downwards[1];
      for (int i = 0; i < ssize(adj[v]); i++) {
        int u = adj[v][i];
        line curr_line = weight[v][i];
        if (u != p) {
          self(self, u, v, compose(downwards, curr_line),
            compose(curr_line, upwards), forwards);
        }
      }
    };
    for (int i = 0; i < ssize(adj[cent]); i++) {
      curr_sum_evaluated = 0;
      curr_cnt_nodes = 0;
      dfs(dfs, adj[cent][i], cent, weight[cent][i],
        weight[cent][i], 1);
      total_sum_evaluated =
        total_sum_evaluated + curr_sum_evaluated;
      total_cnt_nodes += curr_cnt_nodes;
    }
    total_sum_evaluated = 0;
    total_cnt_nodes = 0;
    for (int i = ssize(adj[cent]) - 1; i >= 0; i--) {
      curr_sum_evaluated = 0;
      curr_cnt_nodes = 0;
      dfs(dfs, adj[cent][i], cent, weight[cent][i],
        weight[cent][i], 0);
      total_sum_evaluated =
        total_sum_evaluated + curr_sum_evaluated;
      total_cnt_nodes += curr_cnt_nodes;
    }
    for (int v : adj[cent]) {
      for (int i = 0; i < ssize(adj[v]); i++) {
        if (adj[v][i] == cent) {
          swap(weight[v][i], weight[v].back());
          weight[v].pop_back();
          break;
        }
      }
    }
  });
  for (int i = 0; i < n; i++) cout << res[i].x << ' ';
  cout << '\n';
}
