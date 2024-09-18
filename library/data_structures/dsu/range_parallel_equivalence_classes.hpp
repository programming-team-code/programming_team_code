#pragma once
#include "../../../kactl/content/data-structures/UnionFind.h"
//! Given triplets (l1,l2,len), joins (l1,l2),
//!   (l1+1,l2+1), ..., (l1+len-1,l2+len-1)
//! @time O((n + q) * α(n))
//! @space O(n + q)
UF get_range_parallel_equivalence_classes(
  const vector<array<int, 3>>& rests, int n) {
  vector<vector<array<int, 2>>> rests_by_len(n + 1);
  for (auto [l1, l2, len] : rests)
    rests_by_len[len].push_back({l1, l2});
  UF uf(n);
  for (int len = n; len > 0; len--)
    for (auto [l1, l2] : rests_by_len[len])
      if (uf.join(l1, l2))
        rests_by_len[len - 1].push_back({l1 + 1, l2 + 1});
  return uf;
}
