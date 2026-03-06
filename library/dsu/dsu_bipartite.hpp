#pragma once
//! https://cp-algorithms.com/data_structures/disjoint_set_union.html#support-the-parity-of-the-path-length-checking-bipartiteness-online
//! DSU with support for parity of path to root for online
//! bipartite check
struct dsu_bipartite {
  vi p, is_bi, parity;
  dsu_bipartite(int n): p(n, -1), is_bi(n, 1), parity(n) {}
  int f(int v) {
    if (p[v] < 0) return v;
    int root = f(p[v]);
    return parity[v] ^= parity[p[v]], p[v] = root;
  }
  int size(int v) { return -p[f(v)]; }
  bool is_bipartite(int v) { return is_bi[f(v)]; }
  bool join(int u, int v) {
    int root_u = f(u), root_v = f(v);
    int new_parity = parity[u] ^ parity[v];
    if ((u = root_u) == (v = root_v)) {
      is_bi[u] &= new_parity;
      return 0;
    }
    if (p[u] > p[v]) swap(u, v);
    is_bi[u] &= is_bi[v];
    parity[v] = new_parity ^ 1;
    p[u] += p[v], p[v] = u;
    return 1;
  }
};
