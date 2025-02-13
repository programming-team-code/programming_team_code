/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via
 * LCA.cpp
 */
vector<vector<int>> treeJump(vector<int>& P) {
  int on = 1, d = 1;
  while (on < ssize(P)) on *= 2, d++;
  vector<vector<int>> jmp(d, P);
  for (int i = 1; i < d; i++)
    for (int j = 0; j < ssize(P); j++)
      jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
  return jmp;
}
int jmp(vector<vector<int>>& tbl, int nod, int steps) {
  for (int i = 0; i < ssize(tbl); i++)
    if (steps & (1 << i)) nod = tbl[i][nod];
  return nod;
}
int lca(vector<vector<int>>& tbl, vector<int>& depth,
  int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  a = jmp(tbl, a, depth[a] - depth[b]);
  if (a == b) return a;
  for (int i = ssize(tbl); i--;) {
    int c = tbl[i][a], d = tbl[i][b];
    if (c != d) a = c, b = d;
  }
  return tbl[0][a];
}
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
  vector<vector<int>> b_tbl;
  vector<int> d, p, dl, idx_l, l_tbl;
  //! @param adj forest (rooted or unrooted)
  //! @time O(n log n)
  //! @space O(n log n) for b_tbl. Everything else is O(n)
  ladder(const auto& adj):
    n(ssize(adj)), d(n), p(n, -1), dl(n), idx_l(n) {
    auto dfs = [&](auto&& self, int v) -> void {
      dl[v] = v;
      for (int u : adj[v])
        if (u != p[v]) {
          d[u] = d[p[u] = v] + 1;
          self(self, u);
          if (d[dl[u]] > d[dl[v]]) dl[v] = dl[u];
        }
    };
    for (int i = 0; i < n; i++) {
      if (p[i] == -1) p[i] = i, dfs(dfs, i);
      if (p[i] == i || dl[p[i]] != dl[i]) {
        int v = dl[i], len = (d[v] - d[i]) * 2;
        idx_l[v] = ssize(l_tbl) + d[v];
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
