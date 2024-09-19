#pragma once
#include "../../library/trees/centroid_decomp_uncommon/centroid_decomp_uncommon.hpp"
void cd_asserts(const vector<vector<int>>& adj) {
  vector<bool> seen_cent(sz(adj));
  centroid(adj,
    [&](const vector<vector<int>>& cd_adj,
      int cent) -> void {
      assert(!seen_cent[cent]);
      seen_cent[cent] = 1;
      auto dfs = [&](auto&& self, int u, int p) -> int {
        int sub_size = 1;
        for (int v : cd_adj[u])
          if (v != p) sub_size += self(self, v, u);
        return sub_size;
      };
      int sz_decomp = dfs(dfs, cent, -1);
      int sum = 1;
      for (int u : cd_adj[cent]) {
        int sz_subtree = dfs(dfs, u, cent);
        sum += sz_subtree;
        assert(
          1 <= sz_subtree && 2 * sz_subtree <= sz_decomp);
      }
      assert(sum == sz_decomp);
    });
  assert(find(begin(seen_cent), end(seen_cent), 0) ==
    end(seen_cent));
}
