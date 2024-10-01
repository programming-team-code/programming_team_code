#pragma once
//! https://mzhang2021.github.io/cp-blog/kruskal/
//! @time O(n log n)
//! @space O(n)
struct kr_tree {
  int id;
  vi p;
  vector<vi> adj;
  kr_tree(int n) : id(n), p(2 * n, -1), adj(2 * n) {}
  int find(int v) { return p[v] < 0 ? v : p[v] = find(p[v]); }
  bool join(int u, int v) {
    if ((u = find(u)) == (v = find(v))) return 0;
    return adj[p[u] = p[v] = id++] = {u, v}, 1;
  }
};
