#pragma once
//! https://mzhang2021.github.io/cp-blog/kruskal/
//! @time O(n log n)
//! @space O(n)
struct kr_tree {
  int id;
  vi p;
  vector<vi> adj;
  kr_tree(int n): id(n), p(2 * n, -1), adj(2 * n) {}
  int f(int u) { return p[u] < 0 ? u : p[u] = f(p[u]); }
  bool join(int u, int v) {
    if ((u = f(u)) == (v = f(v))) return 0;
    return adj[p[u] = p[v] = id++] = {u, v}, 1;
  }
};
