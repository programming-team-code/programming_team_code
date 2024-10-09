struct Dinic {
  struct Edge {
    int to;
    ll c, oc;
    ll flow() { return oc - c; }
  };
  ll max_cap = 0;
  vi lvl, ptr, q;
  vector<vector<int>> adj;
  vector<Edge> edge;
  Dinic(int n): lvl(n), ptr(n), q(n), adj(n) {}
  int addEdge(int a, int b, ll c) {
    adj[a].push_back(sz(edge));
    edge.push_back({b, c, c});
    adj[b].push_back(sz(edge));
    edge.push_back({a, 0, 0});
    max_cap = max(max_cap, c);
    return sz(edge) - 2;
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      Edge& e = edge[adj[v][i]];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, edge[adj[v][i] ^ 1].c += p;
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
            if (Edge e = edge[id]; !lvl[e.to] && e.c / i)
              q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
        }
        while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
      } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
