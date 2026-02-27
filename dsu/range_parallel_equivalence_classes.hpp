struct DSU {
  vector<int> p;
  DSU(int n): p(n, -1) {}
  int size(int u) { return -p[f(u)]; }
  int f(int u) { return p[u] < 0 ? u : p[u] = f(p[u]); }
  bool join(int u, int v) {
    if ((u = f(u)) == (v = f(v))) return 0;
    if (p[u] > p[v]) swap(u, v);
    return p[u] += p[v], p[v] = u, 1;
  }
};
//! @code
//!   vector<vector<pii>> joins(n + 1);
//!   joins[len].emplace_back(u, v);
//!   // it does:
//!   // dsu.join(u + 0, v + 0);
//!   // dsu.join(u + 1, v + 1);
//!   // dsu.join(u + 2, v + 2);
//!   // ...
//!   // dsu.join(u + len - 1, v + len - 1);
//!   DSU dsu = get_rp_dsu(joins, n);
//! @endcode
//! @time O((n + q) * \alpha(n))
//! @space O(n + q)
DSU get_rp_dsu(vector<vector<pair<int, int>>>& joins,
  int n) {
  DSU dsu(n);
  for (int i = n; i; i--)
    for (auto [u, v] : joins[i])
      if (dsu.join(u, v))
        joins[i - 1].emplace_back(u + 1, v + 1);
  return dsu;
}
