/** @file */
#pragma once
#include "scc.hpp"
/**
 * @see https://codeforces.com/blog/entry/15102
 *
 * Add minimum extra directed edges to directed graph to make it strongly connected.
 * If the directed graph is not initially strongly connected, then the edge
 * list's size is max(# zero indegree SCCs, # zero outdegree SCCs)
 *
 * @code{.cpp}
       auto [num_sccs, scc_id] = sccs(adj);
       vector<array<int, 2>> edges = extra_edges(adj, num_sccs, scc_id);
 * @endcode
 * @param adj,num_sccs,scc_id directed graph and its SCCs
 * @returns directed edge list: edges[i][0] -> edges[i][1]
 * @time O(n + m)
 * @space An O(n) edge list is allocated and returned, but multiple O(n + m)
 * vectors are allocated temporarily
 */
vector<array<int, 2>> extra_edges(const vector<vector<int>>& adj, int num_sccs, const vector<int>& scc_id) {
  if (num_sccs == 1) return {};
  int n = ssize(adj);
  vector<vector<int>> scc_adj(num_sccs);
  vector<bool> zero_in(num_sccs, 1);
  for (int i = 0; i < n; i++)
    for (int v : adj[i]) {
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
  vector<array<int, 2>> edges;
  vector<int> in_unused;
  for (int i = 0; i < num_sccs; i++)
    if (zero_in[i]) {
      vis[i] = 1;
      int zero_out = dfs(dfs, i);
      if (zero_out != -1) edges.push_back({zero_out, i});
      else in_unused.push_back(i);
    }
  for (int i = 1; i < ssize(edges); i++) swap(edges[i][0], edges[i - 1][0]);
  for (int i = 0; i < num_sccs; i++)
    if (empty(scc_adj[i]) && !vis[i]) {
      if (!empty(in_unused)) {
        edges.push_back({i, in_unused.back()});
        in_unused.pop_back();
      } else edges.push_back({i, num_sccs - 1});
    }
  for (int u : in_unused) edges.push_back({0, u});
  vector<int> to_node(num_sccs);
  for (int i = 0; i < n; i++) to_node[scc_id[i]] = i;
  for (auto& [u, v] : edges) u = to_node[u], v = to_node[v];
  return edges;
}
