#define PROBLEM \
  "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "../template.hpp"
#include "../../../library/trees/hld.hpp"
#include "../../../library/data_structures_[l,r)/bit.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  HLD<0> hld(adj);
  BIT bit(n);
  for (int i = 0; i < n; i++) bit.update(hld.tin[i], a[i]);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int v, x;
      cin >> v >> x;
      bit.update(hld.tin[v], x);
    } else {
      int u, v;
      cin >> u >> v;
      ll sum = 0;
      hld.path(u, v,
        [&](int l, int r) { sum += bit.query(l, r); });
      cout << sum << '\n';
    }
  }
}
