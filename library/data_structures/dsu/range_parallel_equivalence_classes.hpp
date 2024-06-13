/** @file */
#pragma once
#include "../../../kactl/content/data-structures/UnionFind.h"
/**
 * Given a set of queries (l1, l2, len) such that for each query, we want to
 * join the ranges [l1, l1 + len) and [l2, l2 + len) such that edges of the form
 * (l1 + i, l2 + i) are joined. This data structure allows us to answer these
 * queries in O(n + q) time where n is the number of elements and q is the
 * number of queries.
 *
 * @returns an array `ids` such that `0 <= ids[i] < n` and `ids[i] == ids[j]` if
 * `i` and `j` belong to the same equivalence class
 *
 * @time O((n + q) inverse ack n) amortized across all queries
 * @space O(n + q)
 */
vi get_range_parallel_equivalence_classes(const vector<array<int, 3>>& queries,
                                          int n) {
  vector<vector<array<int, 2>>> queries_by_len(n + 1);
  for (const auto& [l1, l2, len] : queries)
    queries_by_len[len].push_back({l1, l2});
  UF uf(n);
  for (int len = n; len > 0; len--)
    for (auto [l1, l2] : queries_by_len[len])
      if (uf.join(l1, l2)) queries_by_len[len - 1].push_back({l1 + 1, l2 + 1});
  vi ids(n);
  for (int i = 0; i < n; i++) ids[i] = uf.find(i);
  return ids;
}
