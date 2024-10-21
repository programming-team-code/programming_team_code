//! @code
//!   auto [num_distinct_subtrees, iso_id] =
//!     subtree_iso(adj);
//! @endcode
//! - 0 <= iso_id[v] < num_distinct_subtrees
//! - iso_id[u] == iso_id[v] iff subtree u is
//!     isomorphic to subtree v
//! @time O(n log n)
//! @space O(n)
struct subtree_iso {
  int num_distinct_subtrees;
  vector<int> iso_id;
  subtree_iso(const vector<vector<int>>& adj):
    iso_id(ssize(adj), -1) {
    map<vector<int>, int> hashes;
    auto dfs = [&](auto&& self, int v, int p) -> int {
      vector<int> ch_ids;
      for (int u : adj[v])
        if (u != p) ch_ids.push_back(self(self, u, v));
      sort(begin(ch_ids), end(ch_ids));
      return iso_id[v] =
               hashes.try_emplace(ch_ids, ssize(hashes))
                 .first->second;
    };
    for (int i = 0; i < ssize(adj); i++)
      if (iso_id[i] == -1) dfs(dfs, i, i);
    num_distinct_subtrees = ssize(hashes);
  }
};
