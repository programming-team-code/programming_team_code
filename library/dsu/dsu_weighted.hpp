#pragma once
//! @code
//!   dsu_weighted dsu(n);
//!   dsu.join(u, v, w);
//!   // we now know a[u] = a[v] + w
//!   ll w = dsu.diff(u, v)
//!   // satisfies a[u] = a[v] + w based on prior joins
//! @endcode
//! @time O(n + q * \alpha(n))
//! @space O(n)
struct dsu_weighted {
  vi p;
  vector<ll> d;
  dsu_weighted(int n): p(n, -1), d(n) {}
  int f(int u) {
    if (p[u] < 0) return u;
    int root = f(p[u]);
    return d[u] += d[p[u]], p[u] = root;
  }
  int size(int u) { return -p[f(u)]; }
  ll diff(int u, int v) {
    return f(u) == f(v) ? d[v] - d[u] : 1e18;
  }
  bool join(int u, int v, ll w) {
    int root_u = f(u), root_v = f(v);
    w += d[u] - d[v];
    if ((u = root_u) == (v = root_v)) return 0;
    if (p[u] > p[v]) swap(u, v), w = -w;
    return p[u] += p[v], p[v] = u, d[v] = w, 1;
  }
};
