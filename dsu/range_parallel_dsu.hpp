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
//! Given u,v,len; joins (u,v), (u+1,v+1),
//!   ..., (u+len-1,v+len-1)
//! `f` is called at most n-1 times
//! @time O(n*log(n)*\alpha(n) + q)
//! @space O(n log n)
struct rp_dsu {
  vector<DSU> dsus;
  rp_dsu(int n): dsus(bit_width(n + 0u), DSU(n)) {}
  void join(int u, int v, int len, const auto& f) {
    int i = __lg(len);
    join(u, v, f, i);
    join(u + len - (1 << i), v + len - (1 << i), f, i);
  }
  void join(int u, int v, const auto& f, int i) {
    if (!dsus[i].join(u, v)) return;
    if (i == 0) return f(u, v);
    i--;
    join(u, v, f, i);
    join(u + (1 << i), v + (1 << i), f, i);
  }
};
