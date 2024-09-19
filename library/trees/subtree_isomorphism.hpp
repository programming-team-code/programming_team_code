#pragma once
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
  vi iso_id;
  subtree_iso(const vector<vi>& adj): iso_id(sz(adj), -1) {
    map<vi, int> hashes;
    auto dfs = [&](auto&& self, int v, int p) -> int {
      vi ch_ids;
      for (int u : adj[v])
        if (u != p) ch_ids.push_back(self(self, u, v));
      sort(all(ch_ids));
      return iso_id[v] =
               hashes.try_emplace(ch_ids, sz(hashes))
                 .first->second;
    };
    rep(i, 0, sz(adj)) if (iso_id[i] == -1) dfs(dfs, i, i);
    num_distinct_subtrees = sz(hashes);
  }
};
