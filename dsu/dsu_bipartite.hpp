//! https://cp-algorithms.com/data_structures/disjoint_set_union.html#support-the-parity-of-the-path-length-checking-bipartiteness-online
//! DSU with support for parity of path to root for online
//! bipartite check
struct dsu_bipartite {
  vector<int> p, is_bi, parity;
  dsu_bipartite(int n): p(n, -1), is_bi(n, 1), parity(n) {}
  int f(int u) {
    if (p[u] < 0) return u;
    int x = f(p[u]);
    return parity[u] ^= parity[p[u]], p[u] = x;
  }
  int size(int u) { return -p[f(u)]; }
  bool is_bipartite(int u) { return is_bi[f(u)]; }
  bool join(int u, int v) {
    int x = f(u), y = f(v);
    int new_parity = parity[u] ^ parity[v];
    if (x == y) {
      is_bi[x] &= new_parity;
      return 0;
    }
    if (p[x] > p[y]) swap(x, y);
    is_bi[x] &= is_bi[y];
    parity[y] = new_parity ^ 1;
    p[x] += p[y], p[y] = x;
    return 1;
  }
};
