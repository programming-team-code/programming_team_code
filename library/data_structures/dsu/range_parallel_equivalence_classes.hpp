/** @file */
#pragma once
#include "../../../kactl/content/data-structures/UnionFind.h"
/**
 * Given a set of restrictions (l1, l2, len) such that for each query, we want
 * to join the ranges [l1, l1 + len) and [l2, l2 + len) such that edges of the
 * form (l1 + i, l2 + i) are joined for all `i` in [0, len).
 *
 * @param rest the vector of restrictions of the form (l1, l2, len)
 * @param n the number of elements
 *
 * @returns a dsu satisfying the equivalences classes
 *
 * @time O((n + q) inverse ack n) amortized across all queries
 * @space O(n + q)
 */
UF get_range_parallel_equivalence_classes(const vector<array<int, 3>>& rest,
                                          int n) {
  vector<vector<array<int, 2>>> queries_by_len(n + 1);
  for (auto [l1, l2, len] : queries) queries_by_len[len].push_back({l1, l2});
  UF uf(n);
  for (int len = n; len > 0; len--)
    for (auto [l1, l2] : queries_by_len[len])
      if (uf.join(l1, l2)) queries_by_len[len - 1].push_back({l1 + 1, l2 + 1});
  return uf;
}
