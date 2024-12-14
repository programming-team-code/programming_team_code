#pragma once
#include "scc.hpp"
//! https://codeforces.com/blog/entry/91608
//! @code
//!   auto joins = offline_incremental_scc(eds, n);
//! @endcode
//! joins[i] = minimum prefix of edges [0, joins[i]] for
//!   eds[i][0] and eds[i][1] to be in the same SCC
//! joins[i] = m if they're never in the same SCC
//! joins[i] = -1 if eds[i][0] == eds[i][1]
//! @time O((n + m) log m)
//! @space O(n + m)
vi offline_incremental_scc(vector<array<int, 2>> eds,
  int n) {
  int m = sz(eds);
  vi ids(n, -1), joins(m, m), idx(m);
  iota(all(idx), 0);
  auto divide_and_conquer = [&](auto&& self, auto el,
                              auto er, int tl, int tr) {
    int mid = tl + (tr - tl) / 2;
    vi vs;
    vector<vi> adj;
    for (auto it = el; it != er; it++) {
      auto& [u, v] = eds[*it];
      for (int w : {u, v}) {
        if (ids[w] != -1) continue;
        ids[w] = sz(vs);
        vs.push_back(w);
        adj.emplace_back();
      }
      u = ids[u], v = ids[v];
      if (*it <= mid) adj[u].push_back(v);
    }
    for (int v : vs) ids[v] = -1;
    auto scc_id = sccs(adj).second;
    auto split = partition(el, er, [&](int i) {
      return scc_id[eds[i][0]] == scc_id[eds[i][1]];
    });
    for (auto it = el; it != split; it++) joins[*it] = mid;
    if (tr - tl == 1) return;
    for (auto it = split; it != er; it++) {
      auto& [u, v] = eds[*it];
      u = scc_id[u], v = scc_id[v];
    }
    // deallocate to avoid O(m log m) memory
    vi().swap(vs);
    vector<vi>().swap(adj);
    vi().swap(scc_id);
    self(self, el, split, tl, mid);
    self(self, split, er, mid, tr);
  };
  // uses -1 as the lower bound to correctly handle
  // self-edges
  divide_and_conquer(divide_and_conquer, all(idx), -1, m);
  return joins;
}
