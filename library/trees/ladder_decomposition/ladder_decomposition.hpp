/** @file */
#pragma once
#include "../../../kactl/content/graph/BinaryLifting.h"
/**
 * @see https://codeforces.com/blog/entry/71567#comment-559299 https://youtu.be/0rCFkuQS968
 * @code{.cpp}
       ladder ld(adj);
       // KACTL functions
       int kth_par = jmp(ld.b_tbl, u, k);
       int curr_lca = lca(ld.b_tbl, ld.d, u, v);
 * @endcode
 */
struct ladder {
  int n;
  vector<vector<int>> b_tbl, l_tbl;
  vector<int> dl /*deepest leaf*/, d, p;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n log n)
   * @space O(n log n) for b_tbl. Everything else is O(n)
   */
  ladder(const vector<vector<int>>& adj) : n(sz(adj)), l_tbl(n), dl(n), d(n), p(n, -1) {
    auto dfs = [&](auto&& self, int u) -> void {
      dl[u] = u;
      for (int v : adj[u])
        if (v != p[u]) {
          d[v] = d[p[v] = u] + 1;
          self(self, v);
          if (d[dl[v]] > d[dl[u]]) dl[u] = dl[v];
        }
    };
    for (int i = 0; i < n; i++)
      if (p[i] == -1) p[i] = i, dfs(dfs, i);
    b_tbl = treeJump(p);
    for (int i = 0; i < n; i++)
      if (p[i] == i || dl[p[i]] != dl[i]) {
        int leaf = dl[i];
        auto& lad = l_tbl[leaf];
        lad.resize(min(2 * (d[leaf] - d[i]), d[leaf] + 1), leaf);
        for (int j = 1; j < sz(lad); j++)
          lad[j] = p[lad[j - 1]];
      }
  }
  /**
   * @param u query node
   * @param k number of edges
   * @returns a node k edges up from u. With k=1, this returns u's parent.
   * @time O(1)
   * @space O(1)
   */
  inline int kth_par(int u, int k) {
    assert(0 <= k && k <= d[u]);
    if (k == 0) return u;
    int bit = __lg(k);
    u = b_tbl[bit][u], k -= (1 << bit);
    int leaf = dl[u];
    return l_tbl[leaf][k + d[leaf] - d[u]];
  }
};
