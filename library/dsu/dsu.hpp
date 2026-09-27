#pragma once
// NOLINTNEXTLINE(readability-identifier-naming)
struct DSU {
  vi p;
  DSU(int n): p(n, -1) {}
  int size(int u) { return -p[find(u)]; }
  int find(int u) {
    return p[u] < 0 ? u : p[u] = find(p[u]);
  }
  bool join(int u, int v) {
    if ((u = find(u)) == (v = find(v))) return 0;
    if (p[u] > p[v]) swap(u, v);
    return p[u] += p[v], p[v] = u, 1;
  }
};
