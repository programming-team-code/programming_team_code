#pragma once
#include "../../library/flow/dinic.hpp"
void dinic_asserts(const dinic& d) {
  int n = sz(d.q);
  vector<ll> in_flow(n), out_flow(n);
  for (int v = 0; v < n; v++) {
    for (int id : d.adj[v]) {
      if (id % 2) continue;
      dinic::edge e = d.edges[id];
      out_flow[v] += e.flow();
      in_flow[e.to] += e.flow();
      assert(0 <= e.flow() && e.flow() <= e.oc);
    }
  }
  assert(in_flow[0] == 0);
  assert(out_flow[0] == flow);
  assert(in_flow[n - 1] == flow);
  assert(out_flow[n - 1] == 0);
  for (int i = 1; i < n - 1; i++)
    assert(in_flow[i] == out_flow[i]);
  {
    queue<int> q;
    q.push(0);
    vector<bool> vis(n);
    vis[0] = 1;
    while (!empty(q)) {
      int v = q.front();
      q.pop();
      for (int id : d.adj[v]) {
        dinic::edge e = d.edges[id];
        if (e.flow() == e.oc) continue;
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
