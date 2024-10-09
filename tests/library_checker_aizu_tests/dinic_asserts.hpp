#pragma once
void dinic_asserts(dinic& d, int source, int sink,
  ll total_flow) {
  int n = sz(d.q);
  vector<ll> in_flow(n), out_flow(n);
  for (int i = 0; i < sz(d.edges); i += 2) {
    dinic::edge e = d.edges[i];
    out_flow[e.v] += e.flow();
    in_flow[e.to] += e.flow();
    assert(0 <= e.flow() && e.flow() <= e.cap);
  }
  assert(in_flow[source] == 0);
  assert(out_flow[source] == total_flow);
  assert(in_flow[sink] == total_flow);
  assert(out_flow[sink] == 0);
  for (int i = 0; i < n; i++) {
    if (i == source) continue;
    if (i == sink) continue;
    assert(in_flow[i] == out_flow[i]);
  }
  {
    queue<int> q;
    q.push(source);
    vector<bool> vis(n);
    vis[source] = 1;
    while (!empty(q)) {
      int v = q.front();
      q.pop();
      for (int id : d.adj[v]) {
        dinic::edge e = d.edges[id];
        if (e.flow() == e.cap) continue;
        int u = e.to;
        if (!vis[u]) {
          vis[u] = 1;
          q.push(u);
        }
      }
    }
    for (int i = 0; i < n; i++)
      assert(vis[i] == d.left_of_min_cut(i));
  }
}
