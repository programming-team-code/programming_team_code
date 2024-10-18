/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct UF {
  vector<int> e;
  UF(int n): e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) {
    return e[x] < 0 ? x : e[x] = find(e[x]);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
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
  vector<int> order((int)size(w_eds));
  iota(begin(order), end(order), 0);
  sort(begin(order), end(order), [&](int i, int j) {
    return w_eds[i][2] < w_eds[j][2];
  });
  UF uf(n);
  vector<int> ids;
  int64_t cost = 0;
  for (int it : order) {
    auto [u, v, w] = w_eds[it];
    if (uf.join(u, v)) {
      cost += w;
      ids.push_back(it);
    }
  }
  return {cost, ids};
}
