//! @file
#pragma once
#include "../../../kactl/content/graph/BinaryLifting.h"
//! @see https://codeforces.com/blog/entry/71567#comment-559299 https://youtu.be/0rCFkuQS968
//! @code{.cpp}
//!     ladder ld(adj);
//!     // KACTL functions
//!     int kth_par = jmp(ld.b_tbl, v, k);
//!     int curr_lca = lca(ld.b_tbl, ld.d, u, v);
//! @endcode
struct ladder {
  int n;
  vector<vi> b_tbl, l_tbl;
  vi d, p, dl; //!< deepest leaf
  //! @param adj forest (rooted or unrooted)
  //! @time O(n log n)
  //! @space O(n log n) for b_tbl. Everything else is O(n)
  ladder(const vector<vi>& adj):
    n(sz(adj)), l_tbl(n), d(n), p(n, -1), dl(n) {
    auto dfs = [&](auto&& self, int v) -> void {
      dl[v] = v;
      for (int u : adj[v])
        if (u != p[v]) {
          d[u] = d[p[u] = v] + 1;
          self(self, u);
          if (d[dl[u]] > d[dl[v]]) dl[v] = dl[u];
        }
    };
    rep(i, 0, n) if (p[i] == -1) p[i] = i, dfs(dfs, i);
    b_tbl = treeJump(p);
    rep(i, 0, n) if (p[i] == i || dl[p[i]] != dl[i]) {
      int leaf = dl[i];
      vi& lad = l_tbl[leaf];
      lad.resize(min(2 * (d[leaf] - d[i]), d[leaf] + 1),
        leaf);
      rep(j, 1, sz(lad)) lad[j] = p[lad[j - 1]];
    }
  }
  //! @param v query node
  //! @param k number of edges
  //! @returns a node k edges up from v. With k=1, this returns v's parent.
  //! @time O(1)
  //! @space O(1)
  int kth_par(int v, int k) {
    if (k == 0) return v;
    int bit = __lg(k);
    v = b_tbl[bit][v], k -= (1 << bit);
    int leaf = dl[v];
    return l_tbl[leaf][k + d[leaf] - d[v]];
  }
};
