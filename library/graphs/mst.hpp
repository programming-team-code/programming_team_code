#pragma once
#include "../../kactl/content/data-structures/UnionFind.h"
//! @code
//!   auto [mst_cost, ids] = mst(w_eds, n);
//! @endcode
//! mst_cost = sum of edge weights in MST
//! w_eds[ids[i]] = edge in MST
//! @time O(n \alpha(n) + m log m)
//! @space O(n + m)
pair<ll, vi> mst(const vector<array<int, 3>>& w_eds,
  int n) {
  vi order(sz(w_eds));
  iota(all(order), 0);
  sort(all(order), [&](int i, int j) {
    return w_eds[i][2] < w_eds[j][2];
  });
  UF uf(n);
  vi ids;
  ll cost = 0;
  for (int it : order) {
    auto [u, v, w] = w_eds[it];
    if (uf.join(u, v)) {
      cost += w;
      ids.push_back(it);
    }
  }
  return {cost, ids};
}
