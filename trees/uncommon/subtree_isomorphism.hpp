//! @code
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
  vector<int> iso_id(ssize(adj), -1);
  map<vector<int>, int> hashes;
  auto dfs = [&](auto&& self, int u, int p) -> int {
    vector<int> ch_ids;
    for (int v : adj[u])
      if (v != p) ch_ids.push_back(self(self, v, u));
    ranges::sort(ch_ids);
    return iso_id[u] =
             hashes.try_emplace(ch_ids, ssize(hashes))
               .first->second;
  };
  dfs(dfs, 0, 0);
  return pair{ssize(hashes), iso_id};
}
