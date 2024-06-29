/**
 * @returns a vector of size `n` containing the connected component id of each
 * vertex in the complement graph of `adj`
 * guarantee: 0 <= cc_id[u] < number of connected
 * components in the complement graph of adj
 * @param adj adjacency list of the graph
 * @time O(n + m)
 * @space O(n) additional space
 */
vector<int> get_complement_graph_ccs(const vector<vector<int>> &adj) {
  int n = (int)size(adj);
  vector<int> cc_id(n);
  vector<int> unseen(n);
  iota(begin(unseen), end(unseen), 0);
  vector<bool> is_adj(n);
  for (int cnt = 0; !empty(unseen); cnt++) {
    int s = unseen.back();
    unseen.pop_back();
    cc_id[s] = cnt;
    for (queue<int> q({s}); !empty(q);) {
      int u = q.front();
      q.pop();
      for (int v : adj[u]) is_adj[v] = 1;
      vector<int> nxt_unseen;
      for (int v : unseen) {
        if (is_adj[v]) {
          nxt_unseen.push_back(v);
        } else {
          cc_id[v] = cnt;
          q.push(v);
        }
      }
      unseen = move(nxt_unseen);
      for (int v : adj[u]) is_adj[v] = 0;
    }
  }
  return cc_id;
}
