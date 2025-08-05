#pragma once
//! @code
//!   {
//!     vector<vi> adj(n);
//!     auto [num_distinct_subtrees, iso_id] =
//!       subtree_iso(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   auto [num_distinct_subtrees, iso_id] =
//!     subtree_iso(adj);
//! @endcode
//! - 0 <= iso_id[v] < num_distinct_subtrees
//! - iso_id[u] == iso_id[v] iff subtree u is
//!     isomorphic to subtree v
//! @time O(n log n)
//! @space O(n)
auto subtree_iso(const auto& adj) {
  vi iso_id(sz(adj), -1);
  map<vi, int> hashes;
  auto dfs = [&](auto&& self, int v, int p) -> int {
    vi ch_ids;
    for (int u : adj[v])
      if (u != p) ch_ids.push_back(self(self, u, v));
    ranges::sort(ch_ids);
    return iso_id[v] =
             hashes.try_emplace(ch_ids, sz(hashes))
               .first->second;
  };
  dfs(dfs, 0, 0);
  return pair{sz(hashes), iso_id};
}
