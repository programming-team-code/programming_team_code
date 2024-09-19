#pragma once
//! @code
//!   auto cc_id = get_complement_graph_ccs(adj);
//! @endcode
//! 0<=cc_id[v]<number of connected components
//!   in the complement graph
//! cc_id[u] == cc_id[v] if u,v are in the same
//!   cc in the compliment graph
//! @time O(n + m)
//! @space O(n)
vi get_complement_graph_ccs(const vector<vi> &adj) {
  int n = sz(adj);
  vi cc_id(n);
  vi unseen(n);
  iota(all(unseen), 0);
  vector<bool> is_adj(n);
  for (int cnt = 0; !empty(unseen); cnt++) {
    int s = unseen.back();
    unseen.pop_back();
    cc_id[s] = cnt;
    for (queue<int> q({s}); !empty(q);) {
      int v = q.front();
      q.pop();
      for (int u : adj[v]) is_adj[u] = 1;
      vi nxt_unseen;
      for (int u : unseen) {
        if (is_adj[u]) {
          nxt_unseen.push_back(u);
        } else {
          cc_id[u] = cnt;
          q.push(u);
        }
      }
      unseen = move(nxt_unseen);
      for (int u : adj[v]) is_adj[u] = 0;
    }
  }
  return cc_id;
}
