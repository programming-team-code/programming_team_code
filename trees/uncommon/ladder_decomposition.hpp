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
//!   int kth_par = jmp(ld.jmp, v, k);
//!   int curr_lca = lca(ld.jmp, ld.d, u, v);
//! @endcode
struct ladder {
  int n;
  vector<int> d, p, leaf, idx, lad;
  vector<vector<int>> jmp;
  //! @param adj forest (rooted or unrooted)
  //! @time O(n log n)
  //! @space O(n log n) for jmp. Everything else is O(n)
  ladder(const auto& adj):
    n(ssize(adj)), d(n), p(n), leaf(n), idx(n),
    lad(2 * n) {
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
    for (int i = 0; i < n; i++)
      if (p[i] == i || leaf[p[i]] != leaf[i]) {
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
