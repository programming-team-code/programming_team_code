#pragma once
#include "../../library/trees/centroid_decomp.hpp"
void cd_asserts(vector<vector<int>> adj) {
  vector<int> decomp_size(sz(adj), -1);
  vector<int> naive_par_decomp(sz(adj), -1);
  vi par = cd(adj, [&](int cent) -> void {
    assert(decomp_size[cent] == -1);
    auto dfs = [&](auto&& self, int u, int p) -> int {
      if (p != -1) naive_par_decomp[u] = cent;
      int sub_size = 1;
      for (int v : adj[u])
        if (v != p) sub_size += self(self, v, u);
      return sub_size;
    };
    decomp_size[cent] = dfs(dfs, cent, -1);
    for (int u : adj[cent]) {
      int sz_subtree = dfs(dfs, u, cent);
      assert(1 <= sz_subtree &&
        2 * sz_subtree <= decomp_size[cent]);
    }
  });
  assert(par == naive_par_decomp);
  rep(i, 0, sz(adj)) {
    assert(decomp_size[i] >= 1);
    if (par[i] != -1)
      assert(2 * decomp_size[i] <= decomp_size[par[i]]);
  }
}
