#pragma once
//! https://e-maxx.ru/algo/min_cost_flow
//! @code
//!   mcmf f(n);
//!   auto [flow, cost] = f.get_flow(s,t,total_flow);
//! @endcode
//! 0<=s,t<n;
//! flow<=total_flow is the max amount of
//!   flow we can send
//! cost: minimum sum of (edge.flow*edge.cost) over
//!   all ways to send `flow` flow
struct mcmf {
  struct edge {
    int u, v;
    ll cap, cost, flow;
    int back;
  };
  int n;
  vector<edge> e;
  vector<vi> adj;
  mcmf(int a_n): n(a_n), adj(n) {}
  void add_edge(int u, int v, ll cap, ll cost) {
    edge e1 = {u, v, cap, cost, 0, sz(adj[v])};
    edge e2 = {v, u, 0, -cost, 0, sz(adj[u])};
    adj[u].push_back(sz(e));
    e.push_back(e1);
    adj[v].push_back(sz(e));
    e.push_back(e2);
  }
  array<ll, 2> get_flow(int s, int t, ll total_flow) {
    ll flow = 0, cost = 0;
    while (flow < total_flow) {
      vector d(n, LLONG_MAX);
      vi p_edge(n), id(n), q(n), p(n);
      int qh = 0, qt = 0;
      q[qt++] = s;
      d[s] = 0;
      while (qh != qt) {
        int u = q[qh++];
        id[u] = 2;
        if (qh == n) qh = 0;
        rep(i, 0, sz(adj[u])) {
          edge& r = e[adj[u][i]];
          if (r.flow < r.cap && d[u] + r.cost < d[r.v]) {
            d[r.v] = d[u] + r.cost;
            if (id[r.v] == 0) {
              q[qt++] = r.v;
              if (qt == n) qt = 0;
            } else if (id[r.v] == 2) {
              if (--qh == -1) qh = n - 1;
              q[qh] = r.v;
            }
            id[r.v] = 1;
            p[r.v] = u;
            p_edge[r.v] = i;
          }
        }
      }
      if (d[t] == LLONG_MAX) break;
      ll addflow = total_flow - flow;
      for (int u = t; u != s; u = p[u]) {
        int pv = p[u], pr = p_edge[u];
        addflow = min(addflow,
          e[adj[pv][pr]].cap - e[adj[pv][pr]].flow);
      }
      for (int u = t; u != s; u = p[u]) {
        int pv = p[u], pr = p_edge[u],
            r = e[adj[pv][pr]].back;
        e[adj[pv][pr]].flow += addflow;
        e[adj[u][r]].flow -= addflow;
        cost += e[adj[pv][pr]].cost * addflow;
      }
      flow += addflow;
    }
    return {flow, cost};
  }
};
