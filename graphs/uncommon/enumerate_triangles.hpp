//! @code
//!   enumerate_triangles(edges, n,
//!     [&](int u, int v, int w) {
//!       //u, v, w form a triangle
//!   });
//! @endcode
//! @time O(n + m ^ (3/2))
//! @space O(n + m)
void enumerate_triangles(const vector<pair<int, int>>& edges, int n, auto f) {
  vector<int> deg(n);
  for (auto [u, v] : edges) deg[u]++, deg[v]++;
  vector<vector<int>> g(n);
  for (auto [u, v] : edges) {
    if (tie(deg[u], u) > tie(deg[v], v)) swap(u, v);
    g[u].push_back(v);
  }
  vector<bool> seen(n);
  for (auto [u, v] : edges) {
    for (int w : g[u]) seen[w] = 1;
    for (int w : g[v])
      if (seen[w]) f(u, v, w);
    for (int w : g[u]) seen[w] = 0;
  }
}
