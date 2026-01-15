struct DSU {
  vector<int> p;
  DSU(int n): p(n, -1) {}
  int size(int x) { return -p[go(x)]; }
  int go(int x) { return p[x] < 0 ? x : p[x] = go(p[x]); }
  bool join(int a, int b) {
    if ((a = go(a)) == (b = go(b))) return 0;
    if (p[a] > p[b]) swap(a, b);
    return p[a] += p[b], p[b] = a, 1;
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
