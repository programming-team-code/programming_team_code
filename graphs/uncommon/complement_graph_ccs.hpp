//! @code
//!   vector<basic_string<int>> adj;
//!   vi cc_id = get_complement_graph_ccs(adj);
//! @endcode
//! 0<=cc_id[v]<number of connected components
//!   in the complement graph
//! cc_id[u] == cc_id[v] if u,v are in the same
//!   cc in the compliment graph
//! @time O(n + m)
//! @space O(n)
vector<int> get_complement_graph_ccs(const auto& adj) {
  int n = ssize(adj);
  vector<int> cc_id(n), unseen(n);
  iota(begin(unseen), end(unseen), 0);
  vector<bool> is_adj(n);
  for (int cnt = 0; !empty(unseen); cnt++) {
    int s = unseen.back();
    unseen.pop_back();
    cc_id[s] = cnt;
    for (queue<int> q({s}); !empty(q);) {
      int v = q.front();
      q.pop();
      for (int u : adj[v]) is_adj[u] = 1;
      vector<int> nxt_unseen;
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
