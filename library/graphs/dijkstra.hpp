#pragma once
//! @code
//!   vector<vector<pair<int, ll>>> adj(n);
//!   auto d = dijkstra(adj, source);
//! @endcode
//! d[v] = min dist from source->..->v
//! @time O(n + (m log m))
//! @space O(n + m)
vector<ll> dijkstra(
  const vector<vector<pair<int, ll>>>& adj, int s) {
  using p = pair<ll, int>;
  priority_queue<p, vector<p>, greater<>> pq;
  pq.emplace(0, s);
  vector<ll> d(sz(adj), LLONG_MAX);
  while (!empty(pq)) {
    auto [d_v, v] = pq.top();
    pq.pop();
    if (d[v] != LLONG_MAX) continue;
    d[v] = d_v;
    for (auto [u, w] : adj[v]) pq.emplace(w + d_v, u);
  }
  return d;
}
