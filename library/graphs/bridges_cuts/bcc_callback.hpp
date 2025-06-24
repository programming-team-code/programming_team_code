#pragma once
//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
//!   {
//!     vector<vector<int>> adj(n);
//!     vector<pii> edges(m);
//!     UF uf(n);
//!     bcc_callback(adj, [&](const vi& nodes) {
//!       if (sz(nodes) > 2)
//!         for (int v : nodes) uf.join(v, nodes[0]);
//!     });
//!     vector<basic_string<int>> bridge_tree(n);
//!     for (auto [u, v] : edges)
//!       if (!uf.sameSet(u, v)) {
//!         u = uf.find(u), v = uf.find(v);
//!         bridge_tree[u] += v;
//!         bridge_tree[v] += u;
//!       }
//!   }
//!
//!   vector<basic_string<int>> adj(n);
//!   vector<basic_string<array<int, 2>>> adj_edge_ids(n);
//!   vector<bool> seen(m);
//!   bcc_callback(adj, [&](const vi& nodes) {
//!     rep (i, 0, sz(nodes) - 1)
//!       for (auto [v, e_id] : adj_edge_ids[nodes[i]])
//!         if (!seen[e_id]) {
//!           seen[e_id] = 1;
//!           // this edge is in the current BCC
//!         }
//!   });
//! @endcode
//! callback not called on components with a single node
//! @time O(n + m)
//! @space O(n + m)
void bcc_callback(const auto& adj, auto f) {
  int n = sz(adj), q = 0, s = 0;
  vi tin(n), st(n);
  auto dfs = [&](auto&& self, int v) -> int {
    int l = tin[v] = ++q;
    for (int u : adj[v]) {
      int siz = s, lu = 0;
      l = min(l, tin[u] ?: (lu = self(self, st[s++] = u)));
      if (lu >= tin[v]) {
        st[s++] = v;
        f(vi(siz + all(st) - n + s));
        s = siz;
      }
    }
    return l;
  };
  rep(i, 0, n) if (!tin[i]) dfs(dfs, i);
}
