#pragma once
//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
//!   {
//!     vector<vi> adj(n);
//!     UF uf(n);
//!     vector<bool> seen(n);
//!     bcc(adj, [&](const vi& nodes) {
//!       int count_edges = 0;
//!       rep (i, 0, sz(nodes) - 1) {
//!         seen[nodes[i]] = 1;
//!         for (int u : adj[nodes[i]]) if (!seen[u]) {
//!           // edge nodes[i] <=> u is in current BCC
//!           count_edges++;
//!         }
//!       }
//!       if (count_edges == 1) {
//!         // nodes[0] <=> nodes[1] is a bridge
//!         return;
//!       }
//!       for (int u : nodes) uf.join(u, nodes[0]);
//!     });
//!     vector<basic_string<int>> bridge_tree(n);
//!     rep (i, 0, n)
//!       for (int u : adj[i])
//!         if (!uf.sameSet(i, u))
//!           bridge_tree[uf.find(i)] += uf.find(u);
//!   }
//!
//!   vector<basic_string<int>> adj(n);
//!   vector<basic_string<int>> block_vertex_tree(2 * n);
//!   int bcc_id = n;
//!   bcc(adj, [&](const vi& nodes) {
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
void bcc(const auto& adj, auto f) {
  int n = sz(adj), q = 0, s = 0;
  vi t(n), st(n);
  auto dfs = [&](auto&& self, int u) -> int {
    int l = t[u] = ++q;
    for (int v : adj[u]) {
      int siz = s, lu = 0;
      l = min(l, t[v] ?: (lu = self(self, st[s++] = v)));
      if (lu >= t[u]) {
        st[s++] = u;
        f({siz + all(st) - n + s});
        s = siz;
      }
    }
    return l;
  };
  rep(i, 0, n) if (!t[i]) dfs(dfs, i);
}
