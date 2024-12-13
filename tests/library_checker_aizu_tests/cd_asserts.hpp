#pragma once
#include "../../library/trees/centroid_decomp.hpp"
void cd_asserts(const vector<vector<int>>& adj) {
  vector<int> decomp_size(sz(adj), -1);
  vector<int> naive_par_decomp(sz(adj), -1);
  centroid(adj,
           [&](const vector<vector<int>>& cd_adj, int cent,
               int par_cent) -> void {
             assert(naive_par_decomp[cent] == par_cent);
             assert(decomp_size[cent] == -1);
             auto dfs = [&](auto&& self, int u, int p) -> int {
               naive_par_decomp[u] = cent;
               int sub_size = 1;
               for (int v : cd_adj[u])
                 if (v != p) sub_size += self(self, v, u);
               return sub_size;
             };
             decomp_size[cent] = dfs(dfs, cent, -1);
             if (par_cent != -1)
               assert(1 <= decomp_size[cent] &&
                      2 * decomp_size[cent] <= decomp_size[par_cent]);
             for (int u : cd_adj[cent]) {
               int sz_subtree = dfs(dfs, u, cent);
               assert(1 <= sz_subtree &&
                      2 * sz_subtree <= decomp_size[cent]);
             }
           });
  rep(i, 0, sz(adj)) assert(decomp_size[i] >= 1);
}
