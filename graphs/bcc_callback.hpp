//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
//!   {
//!     vector<vector<int>> g(n);
//!     DSU dsu(n);
//!     vector<bool> vis(n);
//!     bcc(g, [&](const vector<int>& nodes) {
//!       int cnt_edges = 0;
//!       for (int i = 0; i < ssize(nodes) - 1; i++) {
//!         vis[nodes[i]] = 1;
//!         for (int u : g[nodes[i]]) if (!vis[u]) {
//!           // edge nodes[i] <=> u is in current BCC
//!           cnt_edges++;
//!         }
//!       }
//!       if (cnt_edges == 1) {
//!         // nodes[0] <=> nodes[1] is a bridge
//!         return;
//!       }
//!       for (int u : nodes) dsu.join(u, nodes[0]);
//!     });
//!     vector<basic_string<int>> bridge_tree(n);
//!     for (int i = 0; i < n; i++)
//!       for (int u : g[i])
//!         if (dsu.f(i) != dsu.f(u))
//!           bridge_tree[dsu.f(i)] += dsu.f(u);
//!   }
//!
//!   vector<basic_string<int>> g(n);
//!   vector<basic_string<int>> block_vertex_tree(2 * n);
//!   int bcc_id = n;
//!   bcc(g, [&](const vector<int>& nodes) {
//!     for (int u : nodes) {
//!       block_vertex_tree[u] += bcc_id;
//!       block_vertex_tree[bcc_id] += u;
//!     }
//!     bcc_id++;
//!   });
//! @endcode
//! callback not called on components with a single node
//! @time O(n + m)
//! @space O(n)
void bcc(const auto& g, auto f) {
  int n = ssize(g), q = 0, s = 0;
  vector<int> t(n), st(n);
  auto dfs = [&](this auto&& dfs, int u) -> int {
    int l = t[u] = ++q;
    for (int v : g[u]) {
      int siz = s, lu = 0;
      l = min(l, t[v] ?: (lu = dfs(st[s++] = v)));
      if (lu >= t[u]) {
        st[s++] = u;
        f({siz + begin(st), end(st) - n + s});
        s = siz;
      }
    }
    return l;
  };
  for (int i = 0; i < n; i++)
    if (!t[i]) dfs(i);
}
