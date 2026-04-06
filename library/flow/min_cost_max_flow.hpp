#pragma once
//! https://e-maxx.ru/algo/min_cost_flow
//! @code
//!   mcmf f(n);
//!   auto [flow, total_cost] =
//!     f.get_flow(source,sink,total_flow);
//! @endcode
//! 0<=source,sink<n
//! flow<=total_flow is the max amount of
//!   flow we can send
//! total_cost: minimum sum of (edge.flow*edge.cost) over
//!   all ways to send `flow` flow
struct mcmf {
  struct edge {
    int u, v;
    ll cap, cost, flow, back;
  };
  int n;
  vector<edge> e;
  vector<vi> g;
  mcmf(int n): n(n), g(n) {}
  void add_edge(int u, int v, ll cap, ll cost) {
    edge e1 = {u, v, cap, cost, 0, sz(g[v])};
    edge e2 = {v, u, 0, -cost, 0, sz(g[u])};
    g[u].push_back(sz(e));
    e.push_back(e1);
    g[v].push_back(sz(e));
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
        rep(i, 0, sz(g[u])) {
          edge& r = e[g[u][i]];
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
          e[g[pv][pr]].cap - e[g[pv][pr]].flow);
      }
      for (int u = t; u != s; u = p[u]) {
        int pv = p[u], pr = p_edge[u],
            r = e[g[pv][pr]].back;
        e[g[pv][pr]].flow += addflow;
        e[g[u][r]].flow -= addflow;
        cost += e[g[pv][pr]].cost * addflow;
      }
      flow += addflow;
    }
    return {flow, cost};
  }
};
