//! @file
#pragma once
#include "scc.hpp"
//! @see [Radecki Algorithm!](https://codeforces.com/blog/entry/91608)
//!
//! @param edge_updates directed edges {u, v} where u -> v
//! @param n number of vertices
//!
//! @returns a vec joins where joins[i] = minimum prefix of edges [0, joins[i]]
//! for eds[i][0] and eds[i][1] to be in the same SCC; iff eds[i][0] and
//! eds[i][1] are never in the same SCC then joins[i] = m
//!
//! @note for self-edges (u, u), joins[i] = -1
//!
//! @time O((n + m) log m)
//! @space O(n + m)
vi offline_incremental_scc(
  vector<array<int, 2>> edge_updates, int n) {
  int m = sz(edge_updates);
  vi ids(n, -1), joins(m, m);
  vector<array<int, 3>> eds(m);
  rep(t, 0, m) {
    auto [u, v] = edge_updates[t];
    eds[t] = {u, v, t};
  }
  auto divide_and_conquer = [&](auto&& self, auto el,
                              auto er, int tl, int tr) {
    int mid = tl + (tr - tl) / 2;
    vi vs;
    vector<vi> adj;
    for (auto it = el; it != er; it++) {
      auto& [u, v, t] = *it;
      for (int w : {u, v}) {
        if (ids[w] != -1) continue;
        ids[w] = sz(vs);
        vs.push_back(w);
        adj.emplace_back();
      }
      u = ids[u], v = ids[v];
      if (t <= mid) adj[u].push_back(v);
    }
    for (int v : vs) ids[v] = -1;
    auto scc_id = sccs(adj).scc_id;
    auto split = partition(el, er, [&](const auto& ed) {
      return scc_id[ed[0]] == scc_id[ed[1]];
    });
    for (auto it = el; it != split; it++)
      joins[it->back()] = mid;
    if (tr - tl == 1) return;
    for (auto it = split; it != er; it++) {
      auto& [u, v, t] = *it;
      u = scc_id[u], v = scc_id[v];
    }
    // deallocate to avoid O(m log m) memory
    vi().swap(vs);
    vector<vi>().swap(adj);
    vi().swap(scc_id);
    self(self, el, split, tl, mid);
    self(self, split, er, mid, tr);
  };
  // uses -1 as the lower bound to correctly handle self-edges
  divide_and_conquer(divide_and_conquer, all(eds), -1, m);
  return joins;
}
