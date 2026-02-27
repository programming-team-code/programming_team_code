//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/Dinic.h
//! @code
//!   const int src = n, snk = n + 1;
//!   dinic dn(n + 2);
//!   int e_id = dn.add_edge(u, v, cap);
//!   ll tot_flow = dn.calc(src, snk);
//!   dinic::edge an_edge = dn.edges[e_id];
//! @endcode
//! @time O(n * m * log(max_cap))
//!       O(min(sqrt(m), n^(2/3)) * m) if max_cap==1
//!       O(m * sqrt(n)) for bipartite matching
//! @space O(n + m)
struct dinic {
  struct edge {
    int v, to;
    int64_t c, cap;
    int64_t flow() { return cap - c; }
  };
  int64_t max_cap = 1;
  vector<int> lvl, ptr, q;
  vector<vector<int>> adj;
  vector<edge> edges;
  dinic(int n): lvl(n), ptr(n), q(n), adj(n) {}
  int add_edge(int a, int b, int64_t c) {
    adj[a].push_back(ssize(edges));
    edges.push_back({a, b, c, c});
    adj[b].push_back(ssize(edges));
    edges.push_back({-1, a, 0, -1});
    max_cap = max(max_cap, c);
    return ssize(edges) - 2;
  }
  int64_t dfs(int v, int t, int64_t f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < ssize(adj[v]); i++) {
      edge& e = edges[adj[v][i]];
      if (lvl[e.to] == lvl[v] + 1)
        if (int64_t p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, edges[adj[v][i] ^ 1].c += p;
          return p;
        }
    }
    return 0;
  }
  int64_t calc(int s, int t) {
    int64_t flow = 0;
    q[0] = s;
    for (int64_t i = max_cap; i; i /= 2) do {
        lvl = ptr = vector<int>(ssize(q));
        int qi = 0, qe = lvl[s] = 1;
        while (qi < qe && !lvl[t]) {
          int v = q[qi++];
          for (int id : adj[v])
            if (edge e = edges[id]; !lvl[e.to] && e.c >= i)
              q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
        }
        while (int64_t p = dfs(s, t, LLONG_MAX)) flow += p;
      } while (lvl[t]);
    return flow;
  }
  bool left_of_min_cut(int v) { return lvl[v]; }
};
