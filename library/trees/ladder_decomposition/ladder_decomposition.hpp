#pragma once
#include "../../../kactl/content/graph/BinaryLifting.h"
//! https://codeforces.com/blog/entry/71567#comment-559299
//! https://youtu.be/0rCFkuQS968
//! @code
//!   ladder ld(adj);
//!   // KACTL functions
//!   int kth_par = jmp(ld.jmp, v, k);
//!   int curr_lca = lca(ld.jmp, ld.d, u, v);
//! @endcode
struct ladder {
  int n;
  vi d, p, leaf, idx, lad;
  vector<vi> jmp;
  //! @param adj forest (rooted or unrooted)
  //! @time O(n log n)
  //! @space O(n log n) for jmp. Everything else is O(n)
  ladder(const auto& adj):
    n(sz(adj)), d(n), p(n), leaf(n), idx(n), lad(2 * n) {
    auto dfs = [&](auto&& self, int v) -> void {
      leaf[v] = v;
      for (int u : adj[v])
        if (u != p[v]) {
          d[u] = d[p[u] = v] + 1;
          self(self, u);
          if (d[leaf[v]] < d[leaf[u]]) leaf[v] = leaf[u];
        }
    };
    dfs(dfs, 0);
    int pos = 0;
    rep(i, 0, n) if (p[i] == i || leaf[p[i]] != leaf[i]) {
      int l = leaf[i];
      int len = min((d[l] - d[i]) * 2, d[l] + 1);
      idx[l] = pos;
      for (; len--; l = p[l]) lad[pos++] = l;
    }
    jmp = treeJump(p);
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
    v = jmp[bit][v], k -= (1 << bit);
    int l = idx[leaf[v]] + d[leaf[v]] - d[v];
    assert(lad[l] == v);
    // subarray [l, l+k] of lad corresponds to the rest
    // of the jump
    return lad[l + k];
  }
};
