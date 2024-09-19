#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "frequency_table_of_tree_distance"
#include "../template.hpp"
#include "../cd_asserts.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/trees/centroid_decomp/count_paths_per_node.hpp"
#include "../../../library/trees/centroid_decomp/count_paths_per_length.hpp"
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
  if (n >= 2) {
    int k = rnd(1, n - 1);
    vector<ll> count_paths = count_paths_per_node(adj, k);
    ll sum = accumulate(begin(count_paths),
      end(count_paths), 0LL);
    assert(sum % (k + 1) == 0);
    assert(sum / (k + 1) == cnt_len[k]);
  }
  for (int i = 1; i < n; i++) cout << cnt_len[i] << " ";
  cout << '\n';
  return 0;
}
