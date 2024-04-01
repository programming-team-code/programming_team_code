/** @file */
#pragma once
/**
 * @code{.cpp}
       auto [num_distinct_subtrees, iso_id] = subtree_iso(adj);
 * @endcode
 */
struct subtree_iso {
  int num_distinct_subtrees; /**< number of classes (by iso.) of subtrees */
  /**
   * - 0 <= iso_id[u] < num_distinct_subtrees
   * - iso_id[u] == iso_id[v] iff subtree u is isomorphic to subtree v
   */
  vector<int> iso_id;
  /**
   * @param adj rooted forest (rooted or unrooted)
   * @time O(n log n)
   * @space `iso_id` and `hashes` both are O(n)
   */
  subtree_iso(const vector<vector<int>>& adj) : iso_id(sz(adj), -1) {
    map<vector<int>, int> hashes;
    auto dfs = [&](auto&& self, int u, int p) -> int {
      vector<int> ch_ids;
      ch_ids.reserve(sz(adj[u]));
      for (int v : adj[u])
        if (v != p) ch_ids.push_back(self(self, v, u));
      sort(begin(ch_ids), end(ch_ids));
      return iso_id[u] = hashes.try_emplace(ch_ids, sz(hashes)).first->second;
    };
    for (int i = 0; i < sz(adj); i++)
      if (iso_id[i] == -1) dfs(dfs, i, i);
    num_distinct_subtrees = sz(hashes);
  }
};
