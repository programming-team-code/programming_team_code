#pragma once
#include "../../../kactl/content/graph/BinaryLifting.h"
//! https://codeforces.com/blog/entry/71567#comment-559299
//! https://youtu.be/0rCFkuQS968
//! https://codeforces.com/blog/entry/153250
//! @code
//!   ladder ld(g);
//!   ld.kth_par(u, k); // kth parent of u
//!   ld.kth_par(u, 0); // u
//!   ld.kth_par(u, 1); // p[u]
//!   // KACTL functions
//!   int kth_par = jmp(ld.jmp, u, k);
//!   int curr_lca = lca(ld.jmp, ld.d, u, v);
//! @endcode
struct ladder {
  int n;
  vi d, p, idx, lad;
  vector<vi> jmp;
  ladder(const auto& g):
    n(sz(g)), d(n), p(n), idx(n), lad(2 * n) {
    int i = 0;
    auto dfs = [&](auto dfs, int u) -> vi {
      vi path;
      for (int v : g[u])
        if (v != p[u]) {
          d[v] = d[p[v] = u] + 1;
          vi x = dfs(dfs, v);
          if (sz(x) > sz(path)) swap(x, path);
          for (int y : x) idx[y] = i;
          for (int y : x) lad[i++] = y;
          rep(j, 0, min<int>(sz(x), d[v])) lad[i] =
            p[lad[i - 1]], i++;
        }
      path.push_back(u);
      return path;
    };
    vi x = dfs(dfs, 0);
    for (int y : x) idx[y] = i;
    for (int y : x) lad[i++] = y;
    jmp = treeJump(p);
  }
  int kth_par(int u, int k) {
    assert(0 <= k && k <= d[u]);
    if (k == 0) return u;
    int bit = __lg(k);
    u = jmp[bit][u], k -= (1 << bit);
    int i = idx[u], j = i + d[lad[i]] - d[u];
    assert(lad[j] == u);
    // subarray [j, j+k] of lad corresponds to the rest
    // of the jump
    return lad[j + k];
  }
};
