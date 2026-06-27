/**
 * Author: Adam Soltan
 * Date: 2026-01-13
 * License: CC0
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $r$ should be a vector full of
 * $-1$'s of the same size as the right partition. Returns the size of
 * the matching. $r[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(E \sqrt{V})
 * Status: stress-tested by MinimumVertexCover and tested on Library Checker
 */
int hopcroftKarp(vector<vector<int>>& g, vector<int>& r) {
  int n = ssize(g), res = 0;
  vector<int> l(n, -1), q(n), d(n);
  auto dfs = [&](auto f, int u) -> bool {
    int t = exchange(d[u], 0) + 1;
    for (int v : g[u])
      if (r[v] == -1 || (d[r[v]] == t && f(f, r[v]))) return l[u] = v, r[v] = u, 1;
    return 0;
  };
  for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
    for (int i = 0; i < n; i++)
      if (l[i] == -1) q[t++] = i, d[i] = 1;
    for (int i = 0; i < t; i++)
      for (int v : g[q[i]])
        if (r[v] == -1) f = 1;
        else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
    if (!f) return res;
    for (int i = 0; i < n; i++)
      if (l[i] == -1) res += dfs(dfs, i);
  }
}
//! @code
//!   int l_sz, r_sz;
//!   vector<vi> g(l_sz);
//!   g[u].push_back(v); // 0 <= u < l_sz, 0 <= v < r_sz
//!   vi r(r_sz, -1);
//!   int match_sz = hopcroftKarp(g, r);
//!   // r[v] != -1 iff edge r[v] <-> v in matching
//!   auto [mvc_l, mvc_r] = cover(g, r);
//!   // mvc_l[u] == 1 iff u in mvc
//! @endcode
//! @time O(n + q * log n)
//! @space O(n * \alpha(n))
pair<vector<int>, vector<int>> cover(const vector<vector<int>>& g, vector<int>& r) {
  int n = ssize(g), t = 0;
  vector<int> cl(n), cr(ssize(r)), q(n);
  for (int u : r)
    if (u != -1) cl[u] = 1;
  for (int i = 0; i < n; i++)
    if (!cl[i]) q[t++] = i;
  for (int i = 0; i < t; i++)
    for (int v : g[q[i]]) {
      cr[v] = 1;
      if (r[v] != -1 && cl[r[v]]) cl[q[t++] = r[v]] = 0;
    }
  return {cl, cr};
}
