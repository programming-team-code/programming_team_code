#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "common_interval_decomposition_tree"
#include "../template.hpp"
#include "../perm_tree_asserts.hpp"

#include "../../../library/data_structures/uncommon/permutation_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  perm_tree pt = perm_tree_asserts(a);
  auto root = pt.root;
  auto adj = pt.adj;
  cout << sz(adj) << '\n';
  int curr_time = 0;
  vector<int> node_to_time(sz(adj), -1);
  auto dfs = [&](
               auto&& self, int u, int p) -> void {
    node_to_time[u] = curr_time++;
    cout << (p == -1 ? p : node_to_time[p]) << " "
         << pt.t[u].mn_idx << " "
         << pt.t[u].mn_idx + pt.t[u].len - 1 << " "
         << (pt.t[u].is_join || empty(adj[u])
                ? "linear"
                : "prime")
         << '\n';
    for (int v : adj[u]) self(self, v, u);
  };
  dfs(dfs, root, -1);
  return 0;
}
