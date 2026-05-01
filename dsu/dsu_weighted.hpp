//! @code
//!   dsu_weighted dsu(n);
//!   dsu.join(u, v, w);
//!   // we now know a[u] = a[v] + w
//!   ll w = dsu.diff(u, v);
//!   // satisfies a[u] = a[v] + w based on prior joins
//! @endcode
//! @time O(n + q * \alpha(n))
//! @space O(n)
struct dsu_weighted {
  vector<int> p;
  vector<int64_t> d;
  dsu_weighted(int n): p(n, -1), d(n) {}
  int f(int u) {
    if (p[u] < 0) return u;
    int x = f(p[u]);
    return d[u] += d[p[u]], p[u] = x;
  }
  int size(int u) { return -p[f(u)]; }
  int64_t diff(int u, int v) { return f(u) == f(v) ? d[v] - d[u] : 1e18; }
  bool join(int u, int v, int64_t w) {
    int x = f(u), y = f(v);
    if (x == y) return 0;
    w += d[u] - d[v];
    if (p[x] > p[y]) swap(x, y), w = -w;
    return p[x] += p[y], p[y] = x, d[y] = w, 1;
  }
};
