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
  vector<int> iso_id(ssize(g), -1);
  map<vector<int>, int> hashes;
  [&](this auto&& self, int u, int p) -> int {
    vector<int> ch_ids;
    for (int v : g[u])
      if (v != p) ch_ids.push_back(self(v, u));
    ranges::sort(ch_ids);
    return iso_id[u] = hashes.try_emplace(ch_ids, ssize(hashes)).first->second;
  }(0, 0);
  return pair{ssize(hashes), iso_id};
}
