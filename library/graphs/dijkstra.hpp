//! @file
#pragma once
//! @param adj directed or undirected, weighted
//! graph
//! @param s start node
//! @returns vector d where d[i] = length of
//! shortest path from s to i
//! @time O(n + (m log m))
//! @space besides the O(n + m) param adj, this
//! function allocates/returns a O(n) distance
//! array. The (temporary) priority queue can grow
//! to size O(m)
vector<ll> dijkstra(
  const vector<vector<pair<int, ll>>>& adj, int s) {
  priority_queue<pair<ll, int>,
    vector<pair<ll, int>>, greater<>>
    pq;
  pq.emplace(0, s);
  vector<ll> d(sz(adj), LLONG_MAX);
  while (!empty(pq)) {
    auto [d_v, v] = pq.top();
    pq.pop();
    if (d[v] != LLONG_MAX) continue;
    d[v] = d_v;
    for (auto [u, w] : adj[v])
      pq.emplace(w + d_v, u);
  }
  return d;
}
