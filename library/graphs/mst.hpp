#pragma once
#include "../../kactl/content/data-structures/UnionFind.h"
//! @code
//!   auto [cost, ids] = mst(eds, n);
//! @endcode
//! cost = sum of edge weights in MST
//! eds[ids[i]] = edge in MST
//! @time $O(n \alpha(n) + m log m)$
//! @space O(n + m)
pair<ll, vi> mst(const vector<array<int, 3>>& eds, int n) {
  vi order(sz(eds));
  iota(all(order), 0);
  sort(all(order),
    [&](int i, int j) { return eds[i][2] < eds[j][2]; });
  UF uf(n);
  vi ids;
  ll cost = 0;
  for (int it : order) {
    auto [u, v, w] = eds[it];
    if (uf.join(u, v)) {
      cost += w;
      ids.push_back(it);
    }
  }
  return {cost, ids};
}
