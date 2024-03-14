#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/trees/tree_lift/tree_lift.hpp"

#include "../../../library/trees/linear_lca/linear_lca.hpp"

#include "../../../library/trees/lca_rmq/lca_rmq.hpp"

#include "../compress_tree_asserts.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int par;
    cin >> par;
    adj[par].push_back(i);
  }
  tree_lift tl(adj);
  LCA lc(adj);
  linear_lca lin_lca(adj);
  compress_tree_asserts(adj, lin_lca);
  for (int i = 0; i < n; i++) {
    assert(tl.lca(i, i) == i);
    assert(lc.lca(i, i) == i);
    assert(lc.in_subtree(i, i));
    assert(lin_lca.lca(i, i) == i);
    assert(lin_lca.in_subtree(i, i));
    assert(lc.in[lc.order[i]] == i && lc.order[lc.in[i]] == i);
  }
  while (q--) {
    int u, v;
    cin >> u >> v;
    assert(lc.next_on_path(u, v) == lin_lca.next_on_path(u, v));
    assert(lc.next_on_path(v, u) == lin_lca.next_on_path(v, u));
    assert(lc.in_subtree(u, v) == lin_lca.in_subtree(u, v));
    assert(lc.in_subtree(v, u) == lin_lca.in_subtree(v, u));
    int lca = tl.lca(u, v);
    assert(lca == lc.lca(u, v));
    assert(lca == lin_lca.lca(u, v));
    assert((lca == u) == lc.in_subtree(u, v));
    assert((lca == v) == lc.in_subtree(v, u));
    cout << lca << '\n';
  }
}
