//! https://mzhang2021.github.io/cp-blog/kruskal/
//! @time O(n log n)
//! @space O(n)
struct kr_tree {
  int id;
  vector<int> p;
  vector<vector<int>> adj;
  kr_tree(int n): id(n), p(2 * n, -1), adj(2 * n) {}
  int f(int v) { return p[v] < 0 ? v : p[v] = f(p[v]); }
  bool join(int u, int v) {
    if ((u = f(u)) == (v = f(v))) return 0;
    return adj[p[u] = p[v] = id++] = {u, v}, 1;
  }
};
