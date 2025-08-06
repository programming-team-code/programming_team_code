#define PROBLEM \
  "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../template.hpp"
#include "../edge_cd_asserts.hpp"
#include "../../../library/trees/uncommon/count_paths_per_length.hpp"
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
  { edge_cd(adj, edge_cd_asserts); }
  vector<ll> cnt_len = count_paths_per_length(adj);
  for (int i = 1; i < n; i++) cout << cnt_len[i] << " ";
  cout << '\n';
  return 0;
}
