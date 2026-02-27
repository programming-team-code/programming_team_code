#pragma once
//! https://cp-algorithms.com/data_structures/disjoint_set_union.html#support-the-parity-of-the-path-length-checking-bipartiteness-online
//! DSU with support for parity of path to root for online
//! bipartite check
struct dsu_bipartite {
  int num_sets;
  vi p, is_bi, parity;
  dsu_bipartite(int n):
    num_sets(n), p(n, -1), is_bi(n, 1), parity(n) {}
  int f(int v) {
    if (p[v] < 0) return v;
    int root = f(p[v]);
    parity[v] ^= parity[p[v]];
    return p[v] = root;
  }
  bool join(int u, int v) {
    int root_u = f(u), root_v = f(v);
    if (root_u == root_v) {
      if (parity[u] == parity[v]) is_bi[root_u] = 0;
      return 0;
    }
    if (p[root_u] > p[root_v]) {
      swap(u, v);
      swap(root_u, root_v);
    }
    is_bi[root_u] &= is_bi[root_v];
    parity[root_v] = parity[v] ^ 1 ^ parity[u];
    p[root_u] += p[root_v], p[root_v] = root_u, num_sets--;
    return 1;
  }
  int size(int v) { return -p[f(v)]; }
  bool is_bipartite(int v) { return is_bi[f(v)]; }
};
