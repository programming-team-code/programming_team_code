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
//!       O(m * sqrt(m))
//! @space O(n + m)
struct dinic {
  struct edge {
    int to;
    ll c, oc;
    ll flow() { return oc - c; }
  };
  ll max_cap = 0;
  vi lvl, ptr, q;
  vector<vi> adj;
  vector<edge> edges;
  dinic(int n): lvl(n), ptr(n), q(n), adj(n) {}
  int add_edge(int a, int b, ll c) {
    adj[a].push_back(sz(edges));
    edges.push_back({b, c, c});
    adj[b].push_back(sz(edges));
    edges.push_back({a, 0, 0});
    max_cap = max(max_cap, c);
    return sz(edges) - 2;
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      edge& e = edges[adj[v][i]];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, edges[adj[v][i] ^ 1].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0;
    q[0] = s;
    for (ll i = max_cap; i; i /= 2) do {
        lvl = ptr = vi(sz(q));
        int qi = 0, qe = lvl[s] = 1;
        while (qi < qe && !lvl[t]) {
          int v = q[qi++];
          for (int id : adj[v])
            if (edge e = edges[id]; !lvl[e.to] && e.c / i)
              q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
        }
        while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
      } while (lvl[t]);
    return flow;
  }
  bool left_of_min_cut(int v) { return lvl[v]; }
};
