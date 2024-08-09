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
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};
/**
 * Kruskal's algorithm to find a minimum spanning tree of a graph
 *
 * The implementation will find a minimum spanning forest if the graph is not
 * connected
 *
 * @param eds a list of the edges of the form [u, v, w]
 * @param n the number of vertices in the graph
 * @returns [cost, ids] where `cost` is the total weight of the minimum spanning
 * tree and `ids` is the list of the indices of the edges that are part of the
 * minimum spanning tree
 * @time O(n α(n) + m log m)
 * @space O(n + m)
 */
pair<int64_t, vector<int>> mst(const vector<array<int, 3>>& eds, int n) {
  vector<int> order((int)size(eds));
  iota(begin(order), end(order), 0);
  sort(begin(order), end(order), [&](int i, int j) { return eds[i][2] < eds[j][2]; });
  UF uf(n);
  vector<int> ids;
  int64_t cost = 0;
  for (int it : order) {
    auto [u, v, w] = eds[it];
    if (uf.join(u, v)) {
      cost += w;
      ids.push_back(it);
    }
  }
  return {cost, ids};
}
