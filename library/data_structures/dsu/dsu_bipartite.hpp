/** @file */
#pragma once
/**
 * DSU with support for parity of path to root for online bipartite check
 *
 * @see https://cp-algorithms.com /data_structures/disjoint_set_union.html
 * support-the-parity-of-the-path-length -checking-bipartiteness-online
 */
struct dsu_bipartite {
  int num_sets;
  struct node {
    int p = -1;
    bool is_bi = 1, parity;
  };
  vector<node> t;
  dsu_bipartite(int n) : num_sets(n), t(n) {}
  int find(int u) {
    if (t[u].p < 0) return u;
    int root = find(t[u].p);
    t[u].parity ^= t[t[u].p].parity;
    return t[u].p = root;
  }
  bool join(int u, int v) {
    int root_u = find(u), root_v = find(v);
    if (root_u == root_v) {
      if (t[u].parity == t[v].parity) t[root_u].is_bi = 0;
      return 0;
    }
    if (t[root_u].p > t[root_v].p) {
      swap(u, v);
      swap(root_u, root_v);
    }
    t[root_u].is_bi &= t[root_v].is_bi;
    t[root_v].parity = t[v].parity ^ 1 ^ t[u].parity;
    t[root_u].p += t[root_v].p, t[root_v].p = root_u, num_sets--;
    return 1;
  }
  inline int size(int u) { return -t[find(u)].p; }
  inline bool same_set(int u, int v) { return find(u) == find(v); }
  inline bool is_bipartite(int u) { return t[find(u)].is_bi; }
};
