//! @code
//!   auto d = dijkstra(adj_w, source);
//! @endcode
//! d[v] = min dist from source->..->v
//! @time O(n + (m log m))
//! @space O(n + m)
vector<int64_t> dijkstra(
  const vector<vector<pair<int, int64_t>>>& adj, int s) {
  using p = pair<int64_t, int>;
  priority_queue<p, vector<p>, greater<>> pq;
  pq.emplace(0, s);
  vector<int64_t> d(ssize(adj), LLONG_MAX);
  while (!empty(pq)) {
    auto [d_v, v] = pq.top();
    pq.pop();
    if (d[v] != LLONG_MAX) continue;
    d[v] = d_v;
    for (auto [u, w] : adj[v]) pq.emplace(w + d_v, u);
  }
  return d;
}
