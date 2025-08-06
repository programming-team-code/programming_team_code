#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/trees/uncommon/count_paths_per_node.hpp"
#include "../../../library/trees/lca_rmq.hpp"
#include "../../../library/trees/uncommon/count_paths_per_length.hpp"
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
      assert(path_length_edges < ssize(cnts_naive));
      assert(v < ssize(cnts_naive[path_length_edges]));
      cnts_naive[path_length_edges][v]++;
    }
  }
  return cnts_naive;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 1; n <= 1; n++) {
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
