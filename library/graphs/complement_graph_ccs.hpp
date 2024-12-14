#pragma once
//! @code
//!   vector<vi> adj(n);
//!   vi cc_id = get_complement_graph_ccs(adj);
//!   vector<basic_string<int>> adj1;
//!   vi cc_id2 = get_complement_graph_ccs(adj1);
//! @endcode
//! 0<=cc_id[v]<number of connected components
//!   in the complement graph
//! cc_id[u] == cc_id[v] if u,v are in the same
//!   cc in the compliment graph
//! @time O(n + m)
//! @space O(n)
template<class G>
vi get_complement_graph_ccs(const G& adj) {
  int n = sz(adj);
  vi cc_id(n), unseen(n);
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
      swap(unseen, nxt_unseen);
      for (int u : adj[v]) is_adj[u] = 0;
    }
  }
  return cc_id;
}
