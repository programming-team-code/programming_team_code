#pragma once
struct dsu_weighted {
  int n;
  vi p;
  vector<ll> d;
  dsu_weighted(int n): n(n), p(n, -1), d(n) {}
  int f(int u) {
    if (p[u] < 0) return u;
    int root = f(p[u]);
    d[u] += d[p[u]];
    return p[u] = root;
  }
  int size(int u) { return -p[f(u)]; }
  ll diff(int u, int v) {
    return f(u) == f(v) ? d[v] - d[u] : 1e18;
  }
  bool join(int u, int v, ll w) {
    w += d[u] - d[v];
    u = f(u), v = f(v);
    if (u == v) return 0;
    if (p[u] > p[v]) swap(u, v), w = -w;
    p[u] += p[v];
    p[v] = u;
    d[v] = w;
    return 1;
  }
};
