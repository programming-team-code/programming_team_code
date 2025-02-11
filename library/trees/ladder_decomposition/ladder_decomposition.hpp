#pragma once
#include "../../../kactl/content/graph/BinaryLifting.h"
//! https://codeforces.com/blog/entry/71567#comment-559299
//! https://youtu.be/0rCFkuQS968
//! @code
//!   ladder ld(adj);
//!   // KACTL functions
//!   int kth_par = jmp(ld.b_tbl, v, k);
//!   int curr_lca = lca(ld.b_tbl, ld.d, u, v);
//! @endcode
struct ladder {
  int n;
  vector<vi> b_tbl;
  vi d, p, dl, idx_l, l_tbl;
  //! @param adj forest (rooted or unrooted)
  //! @time O(n log n)
  //! @space O(n log n) for b_tbl. Everything else is O(n)
  ladder(const auto& adj):
    n(sz(adj)), d(n), p(n, -1), dl(n), idx_l(n) {
    auto dfs = [&](auto&& self, int v) -> void {
      dl[v] = v;
      for (int u : adj[v])
        if (u != p[v]) {
          d[u] = d[p[u] = v] + 1;
          self(self, u);
          if (d[dl[u]] > d[dl[v]]) dl[v] = dl[u];
        }
    };
    rep(i, 0, n) {
      if (p[i] == -1) p[i] = i, dfs(dfs, i);
      if (p[i] == i || dl[p[i]] != dl[i]) {
        int v = dl[i], len = (d[v] - d[i]) * 2;
        idx_l[v] = sz(l_tbl) + d[v];
        for (; v != -1 && len--; v = p[v])
          l_tbl.push_back(v);
      }
    }
    b_tbl = treeJump(p);
  }
  //! @param v query node
  //! @param k number of edges
  //! @returns a node k edges up from v. With k=1, this
  //! returns v's parent.
  //! @time O(1)
  //! @space O(1)
  int kth_par(int v, int k) {
    assert(0 <= k && k <= d[v]);
    if (k == 0) return v;
    int bit = __lg(k);
    v = b_tbl[bit][v], k -= (1 << bit);
    int l = idx_l[dl[v]] - d[v];
    assert(l_tbl[l] == v);
    // subarray [l, l+k] of l_tbl corresponds to the rest
    // of the jump
    return l_tbl[l + k];
  }
};
