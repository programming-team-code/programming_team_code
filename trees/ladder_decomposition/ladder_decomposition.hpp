/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
vector<vi> treeJump(vi& P) {
  int on = 1, d = 1;
  while (on < sz(P)) on *= 2, d++;
  vector<vi> jmp(d, P);
  rep(i, 1, d) rep(j, 0, sz(P))
      jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
  return jmp;
}
int jmp(vector<vi>& tbl, int nod, int steps) {
  rep(i, 0, sz(tbl)) if (steps & (1 << i)) nod = tbl[i][nod];
  return nod;
}
int lca(vector<vi>& tbl, vi& depth, int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  a = jmp(tbl, a, depth[a] - depth[b]);
  if (a == b) return a;
  for (int i = sz(tbl); i--;) {
    int c = tbl[i][a], d = tbl[i][b];
    if (c != d) a = c, b = d;
  }
  return tbl[0][a];
}
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
  ladder(const vector<vector<int>>& adj) : n(ssize(adj)), l_tbl(n), dl(n), d(n), p(n, -1) {
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
        for (int j = 1; j < ssize(lad); j++)
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
