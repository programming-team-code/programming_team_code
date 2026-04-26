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
vector<vector<int>> treeJump(vector<int>& P) {
  int on = 1, d = 1;
  while (on < ssize(P)) on *= 2, d++;
  vector<vector<int>> jmp(d, P);
  for (int i = 1; i < d; i++)
    for (int j = 0; j < ssize(P); j++) jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
  return jmp;
}
int jmp(vector<vector<int>>& tbl, int nod, int steps) {
  for (int i = 0; i < ssize(tbl); i++)
    if (steps & (1 << i)) nod = tbl[i][nod];
  return nod;
}
int lca(vector<vector<int>>& tbl, vector<int>& depth, int a, int b) {
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
  vector<int> d, p, idx, l;
  vector<vector<int>> jmp;
  ladder(const auto& g): n(ssize(g)), d(n), p(n), idx(n), l(2 * n) {
    int i = 0;
    vector<int> s(n);
    auto dfs = [&](auto dfs, int u) -> vector<int> {
      vector<int> path;
      s[d[u]] = u;
      for (int v : g[u])
        if (v != p[u]) {
          d[v] = d[p[v] = u] + 1;
          vector<int> x = dfs(dfs, v);
          if (ssize(x) > ssize(path)) swap(x, path);
          for (int y : x) idx[y] = i;
          for (int y : x) l[i++] = y;
          for (int j = 0; j < min(ssize(x), d[v]); j++) l[i++] = s[d[u] - j];
        }
      path.push_back(u);
      return path;
    };
    vector<int> x = dfs(dfs, 0);
    for (int y : x) idx[y] = i;
    for (int y : x) l[i++] = y;
    jmp = treeJump(p);
  }
  int kth_par(int u, int k) {
    assert(0 <= k && k <= d[u]);
    if (k == 0) return u;
    int bit = __lg(k);
    u = jmp[bit][u], k -= (1 << bit);
    int i = idx[u], j = i + d[l[i]] - d[u];
    assert(l[j] == u);
    // subarray [j, j+k] of l corresponds to the rest
    // of the jump
    return l[j + k];
  }
};
