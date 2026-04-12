#pragma once
//! @code
//!   vector<basic_string<int>> g(n);
//!   auto [num_distinct_subtrees, iso_id] =
//!     subtree_iso(g);
//! @endcode
//! - 0 <= iso_id[v] < num_distinct_subtrees
//! - iso_id[u] == iso_id[v] iff subtree u is
//!     isomorphic to subtree v
//! @time O(n log n)
//! @space O(n)
auto subtree_iso(const auto& g) {
  vi iso_id(sz(g), -1);
  map<vi, int> hashes;
  auto dfs = [&](auto dfs, int u, int p) {
    vi ch_ids;
    for (int v : g[u])
      if (v != p) ch_ids.push_back(dfs(dfs, v, u));
    ranges::sort(ch_ids);
    return iso_id[u] =
             hashes.try_emplace(ch_ids, sz(hashes))
               .first->second;
  };
  dfs(dfs, 0, 0);
  return pair{sz(hashes), iso_id};
}
