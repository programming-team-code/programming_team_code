#pragma once
#define RMQ KACTL_RMQ
#define LCA KACTL_LCA
#include "../../kactl/content/graph/CompressTree.h"
#undef RMQ
#undef LCA
#include "../../library/contest/random.hpp"
void compress_tree_asserts(vector<vector<int>> adj,
  LCA& lc_rm) {
  int n = sz(adj);
  vector<bool> used(n);
  KACTL_LCA kactl_lca(adj);
  {
    auto [parent, to_node] = lc_rm.compress_tree({});
    assert(empty(parent) && empty(to_node));
  }
  for (int tests = 0; tests < 10; tests++) {
    vector<int> subset;
    {
      int subset_size = rnd(1, min(n, 10));
      while (subset_size--) {
        int u = rnd(0, n - 1);
        if (!used[u]) {
          used[u] = 1;
          subset.push_back(u);
        }
      }
    }
    auto kactl_res = compressTree(kactl_lca, subset);
    auto [lc_rm_parent, lc_rm_to_node] =
      lc_rm.compress_tree(subset);
    assert(sz(lc_rm_parent) == sz(kactl_res));
    for (int i = 0; i < sz(lc_rm_parent); i++) {
      assert(lc_rm_to_node[i] == kactl_res[i].second);
      assert(lc_rm_parent[i] < i);
      if (i > 0)
        assert(lc_rm_parent[i] == kactl_res[i].first);
      else assert(lc_rm_parent[i] == -1);
    }
    for (int u : subset) used[u] = 0;
  }
}
