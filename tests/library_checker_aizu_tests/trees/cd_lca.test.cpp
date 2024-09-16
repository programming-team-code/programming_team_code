#define PROBLEM \
  "https://judge.yosupo.jp/problem/lca"
// without this, the test runs in like 34 seconds
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../cd_asserts.hpp"

#include "../../../library/trees/centroid_decomp/lca.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int par;
    cin >> par;
    adj[par].push_back(i);
    adj[i].push_back(par);
  }
  cd_asserts(adj);
  cd_lca lca(adj);
  for (int i = 0; i < n; i++) {
    assert(lca.lca(i, i) == i);
  }
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << lca.lca(u, v) << '\n';
  }
}
