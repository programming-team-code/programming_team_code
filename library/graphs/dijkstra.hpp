/** @file */
#pragma once
/**
 * @param adj directed or undirected, weighted graph
 * @param s a node
 * @returns array `d` where `d[i]` = shortest path from node `s` to node
 * `i`. `d[s]` is always 0.
 * @time O((n + m) log n) Note log(m) < log(n^2) = 2*log(n), so O(log n) ==
 * O(log m)
 * @space besides the O(n + m) param `adj`, this function allocates/returns a
 * O(n) distance array. The (temporary) priority queue can grow to size O(n+m)
 */
vector<ll> dijkstra(const vector<vector<pair<int, ll>>>& adj, int s) {
  using node = pair<ll, int>;
  vector<ll> d(sz(adj), LLONG_MAX);
  d[s] = 0;
  priority_queue<node, vector<node>, greater<node>> pq;
  pq.emplace(0, s);
  while (!empty(pq)) {
    auto [d_u, u] = pq.top();
    pq.pop();
    if (d[u] < d_u) continue;  // important check: O(n*m) without it
    d[u] = d_u;
    for (auto [v, w] : adj[u]) pq.emplace(w + d[u], v);
  }
  return d;
}
