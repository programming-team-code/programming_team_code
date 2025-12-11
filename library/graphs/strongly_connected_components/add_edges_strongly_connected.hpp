#pragma once
#include "../scc.hpp"
//! https://codeforces.com/blog/entry/15102
//! Add minimum extra directed edges to directed graph to
//! make it strongly connected. If the directed graph is
//! not initially strongly connected, then the edge list's
//! size is max(# zero indegree SCCs, # zero outdegree
//! SCCs)
//!
//! @code
//!   auto [num_sccs, scc_id] = sccs(adj);
//!   vector<pii> edges = extra_edges(adj,
//!     num_sccs, scc_id);
//! @endcode
//! @param adj,num_sccs,scc_id directed graph and its SCCs
//! @returns directed edge list: edges[i][0] -> edges[i][1]
//! @time O(n + m)
//! @space An O(n) edge list is allocated and returned, but
//! multiple O(n + m) vectors are allocated temporarily
vector<pii> extra_edges(const auto& adj, int num_sccs,
  const vi& scc_id) {
  if (num_sccs == 1) return {};
  int n = sz(adj);
  vector<vi> scc_adj(num_sccs);
  vector<bool> zero_in(num_sccs, 1);
  rep(i, 0, n) for (int v : adj[i]) {
    if (scc_id[i] == scc_id[v]) continue;
    scc_adj[scc_id[i]].push_back(scc_id[v]);
    zero_in[scc_id[v]] = 0;
  }
  vector<bool> vis(num_sccs);
  auto dfs = [&](auto&& self, int u) {
    if (empty(scc_adj[u])) return u;
    for (int v : scc_adj[u])
      if (!vis[v]) {
        vis[v] = 1;
        int zero_out = self(self, v);
        if (zero_out != -1) return zero_out;
      }
    return -1;
  };
  vector<pii> edges;
  vi in_unused;
  rep(i, 0, num_sccs) if (zero_in[i]) {
    vis[i] = 1;
    int zero_out = dfs(dfs, i);
    if (zero_out != -1) edges.emplace_back(zero_out, i);
    else in_unused.push_back(i);
  }
  rep(i, 1, sz(edges))
    swap(edges[i].first, edges[i - 1].first);
  rep(i, 0, num_sccs) if (empty(scc_adj[i]) && !vis[i]) {
    if (!empty(in_unused)) {
      edges.emplace_back(i, in_unused.back());
      in_unused.pop_back();
    } else edges.emplace_back(i, num_sccs - 1);
  }
  for (int u : in_unused) edges.emplace_back(0, u);
  vi to_node(num_sccs);
  rep(i, 0, n) to_node[scc_id[i]] = i;
  for (auto& [u, v] : edges)
    u = to_node[u], v = to_node[v];
  return edges;
}
