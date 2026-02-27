struct DSU {
  vector<int> p;
  DSU(int n): p(n, -1) {}
  int size(int u) { return -p[f(u)]; }
  int f(int u) { return p[u] < 0 ? u : p[u] = f(p[u]); }
  bool join(int u, int v) {
    if ((u = f(u)) == (v = f(v))) return 0;
    if (p[u] > p[v]) swap(u, v);
    return p[u] += p[v], p[v] = u, 1;
  }
};
