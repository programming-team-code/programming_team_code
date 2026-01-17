#pragma once
#include "dsu.hpp"
//! Given triplets (l1,l2,len); joins (l1,l2),
//!   (l1+1,l2+1), ..., (l1+len-1,l2+len-1)
//! @time O((n + q) * \alpha(n))
//! @space O(n + q)
DSU get_rp_dsu(const vector<array<int, 3>>& rests, int n) {
  vector<vector<pii>> rests_by_len(n + 1);
  for (auto [l1, l2, len] : rests)
    rests_by_len[len].emplace_back(l1, l2);
  DSU dsu(n);
  for (int len = n; len > 0; len--)
    for (auto [l1, l2] : rests_by_len[len])
      if (dsu.join(l1, l2))
        rests_by_len[len - 1].emplace_back(l1 + 1, l2 + 1);
  return dsu;
}
