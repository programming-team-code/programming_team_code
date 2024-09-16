#pragma once
#include "../../library/contest/random.hpp"
#include "../../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp"
#include "../../library/graphs/strongly_connected_components/offline_incremental_scc.hpp"
void scc_asserts(const vector<vector<int>>& adj) {
  int n = sz(adj);
  auto [num_sccs, scc_id] = sccs(adj);
  {
    // sanity check for reverse topo order of SCCs
    for (int i = 0; i < n; i++)
      for (auto j : adj[i])
        assert(scc_id[i] >= scc_id[j]);
  }
  vector<bool> is_zero_in(num_sccs, 1),
    is_zero_out(num_sccs, 1);
  for (int i = 0; i < n; i++) {
    for (int v : adj[i]) {
      if (scc_id[i] == scc_id[v]) continue;
      is_zero_in[scc_id[v]] = 0;
      is_zero_out[scc_id[i]] = 0;
    }
  }
  // since {num_sccs-1, ..., 2, 1, 0} is a topo
  // order
  assert(
    is_zero_in[num_sccs - 1] && is_zero_out[0]);
  int num_zero_in = int(
    count(begin(is_zero_in), end(is_zero_in), 1));
  int num_zero_out = int(
    count(begin(is_zero_out), end(is_zero_out), 1));
  vector<pair<int, int>> edges =
    extra_edges(adj, num_sccs, scc_id);
  if (num_sccs == 1) assert(sz(edges) == 0);
  else
    assert(
      sz(edges) == max(num_zero_in, num_zero_out));
  vector<vector<int>> adj_copy(adj);
  for (auto [u, v] : edges) {
    assert(u != v);
    adj_copy[u].push_back(v);
  }
  sccs curr_res(adj_copy);
  assert(curr_res.num_sccs == 1);
}
