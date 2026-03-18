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
//!   auto [mst_cost, ids] = mst(w_eds, n);
//! @endcode
//! mst_cost = sum of edge weights in MST
//! w_eds[ids[i]] = edge in MST
//! @time O(n \alpha(n) + m log m)
//! @space O(n + m)
pair<int64_t, vector<int>> mst(
  const vector<array<int, 3>>& w_eds, int n) {
  vector<int> order(ssize(w_eds));
  iota(begin(order), end(order), 0);
  ranges::sort(order, [&](int i, int j) {
    return w_eds[i][2] < w_eds[j][2];
  });
  DSU dsu(n);
  vector<int> ids;
  int64_t cost = 0;
  for (int it : order) {
    auto [u, v, w] = w_eds[it];
    if (dsu.join(u, v)) {
      cost += w;
      ids.push_back(it);
    }
  }
  return {cost, ids};
}
