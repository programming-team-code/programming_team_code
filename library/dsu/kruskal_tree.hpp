#pragma once
//! https://mzhang2021.github.io/cp-blog/kruskal/
//! requires n >= 1 (2*n-1 allocation underflows when n == 0)
//! @time O(n log n)
//! @space O(n)
struct kr_tree {
  int id;
  vi p;
  vector<vi> g;
  kr_tree(int n): id(n), p(2 * n - 1, -1), g(2 * n - 1) {}
  int f(int u) { return p[u] < 0 ? u : p[u] = f(p[u]); }
  bool join(int u, int v) {
    if ((u = f(u)) == (v = f(v))) return 0;
    return g[p[u] = p[v] = id++] = {u, v}, 1;
  }
};
