#define PROBLEM \
  "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../template.hpp"
#include "../../../library/trees/hld.hpp"
#include "../../../library/data_structures_[l,r)/bit.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  rep(i, 0, n) cin >> a[i];
  vector<vi> adj(n);
  rep(i, 1, n) {
    int par;
    cin >> par;
    adj[par].push_back(i);
    adj[i].push_back(par);
  }
  HLD<1> hld(adj);
  BIT bit(n);
  rep(i, 0, n) bit.update(hld.tin[i], a[i]);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int v, x;
      cin >> v >> x;
      bit.update(hld.tin[v], x);
      a[v] += x;
    } else {
      int v;
      cin >> v;
      auto [l, r] = hld.subtree(v);
      cout << bit.query(l, r) + a[v] << '\n';
    }
  }
}
