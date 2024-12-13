#define PROBLEM \
  "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"
#include "../../../library/trees/linear_kth_path.hpp"
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
  linear_kth_path lin_kth_path(adj);
  while (q--) {
    int u, v, k;
    cin >> u >> v >> k;
    cout << lin_kth_path.kth_path(u, v, k) << '\n';
  }
}
