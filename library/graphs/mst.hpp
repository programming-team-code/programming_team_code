/** @file */
#pragma once
#include "../../kactl/content/data-structures/UnionFind.h"
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
  vector<int> order(ssize(eds));
  iota(begin(order), end(order), 0);
  sort(begin(order), end(order),
       [&](int i, int j) { return eds[i][2] < eds[j][2]; });
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
