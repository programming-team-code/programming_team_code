#pragma once
//! @code
//!   vector<basic_string<array<int, 2>>> g(n);
//!   auto d = dijkstra(g, source);
//! @endcode
//! d[v] = min dist from source->..->v
//! @time O(n + (m log m))
//! @space O(n + m)
vector<ll> dijkstra(const auto& g, int s) {
  using p = pair<ll, int>;
  priority_queue<p, vector<p>, greater<>> pq;
  pq.emplace(0, s);
  vector<ll> d(sz(g), LLONG_MAX);
  while (!empty(pq)) {
    auto [d_v, v] = pq.top();
    pq.pop();
    if (d[v] != LLONG_MAX) continue;
    d[v] = d_v;
    for (auto [u, w] : g[v]) pq.emplace(w + d_v, u);
  }
  return d;
}
