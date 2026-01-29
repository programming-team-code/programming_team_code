//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/HLD.h
//! @code
//!   vector<basic_string<int>> adj(n);
//!   HLD<0> hld(adj);
//!   hld.path(u, v, [&](int l, int r) { // [l, r)
//!   });
//!   auto [l, r] = hld.subtree(u); // [l, r)
//! @endcode
//! @time O(n + q log^2 n)
//! @space O(n)
template<bool VALS_EDGES> struct HLD {
  int n;
  vector<int> p, siz, rt, tin;
  HLD(auto& adj):
    n(ssize(adj)), p(n), siz(n, 1), rt(n), tin(n) {
    auto dfs1 = [&](auto&& self, int u) -> void {
      for (int& v : adj[u]) {
        iter_swap(ranges::find(adj[v], u), rbegin(adj[v]));
        adj[v].pop_back();
        p[v] = u;
        self(self, v);
        siz[u] += siz[v];
        if (siz[v] > siz[adj[u][0]]) swap(v, adj[u][0]);
      }
    };
    dfs1(dfs1, 0);
    int tim = 0;
    auto dfs2 = [&](auto&& self, int u) -> void {
      tin[u] = tim++;
      for (int v : adj[u]) {
        rt[v] = (v == adj[u][0] ? rt[u] : v);
        self(self, v);
      }
    };
    dfs2(dfs2, 0);
  }
  void path(int u, int v, auto f) {
    for (;; v = p[rt[v]]) {
      if (tin[u] > tin[v]) swap(u, v);
      if (rt[u] == rt[v]) break;
      f(tin[rt[v]], tin[v] + 1);
    }
    f(tin[u] + VALS_EDGES, tin[v] + 1);
  }
  pair<int, int> subtree(int u) {
    return {tin[u] + VALS_EDGES, tin[u] + siz[u]};
  }
};
