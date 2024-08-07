/**
 * @param adj directed or undirected, weighted graph
 * @param s start node
 * @returns vector d where d[i] = length of shortest path from s to i
 * @time O(n + (m log m))
 * @space besides the O(n + m) param adj, this function allocates/returns a
 * O(n) distance array. The (temporary) priority queue can grow to size O(m)
 */
vector<int64_t> dijkstra(const vector<vector<pair<int, int64_t>>>& adj, int s) {
  using dt = pair<int64_t, int>;
  priority_queue<dt, vector<dt>, greater<dt>> pq;
  pq.emplace(0, s);
  vector<int64_t> d((int)size(adj), LLONG_MAX);
  while (!empty(pq)) {
    auto [d_v, v] = pq.top();
    pq.pop();
    if (d[v] <= d_v) continue;
    d[v] = d_v;
    for (auto [u, w] : adj[v]) pq.emplace(w + d[v], u);
  }
  return d;
}
