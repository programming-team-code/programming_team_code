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
  int find(int v) {
    if (t[v].p < 0) return v;
    int root = find(t[v].p);
    t[v].parity ^= t[t[v].p].parity;
    return t[v].p = root;
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
  int size(int v) { return -t[find(v)].p; }
  bool same_set(int u, int v) { return find(u) == find(v); }
  bool is_bipartite(int v) { return t[find(v)].is_bi; }
};
