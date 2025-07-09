#pragma once
//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
//!   {
//!     vector<vi> adj(n);
//!     UF uf(n);
//!     vector<bool> seen(n);
//!     bcc_callback(adj, [&](const vi& nodes) {
//!       int count_edges = 0;
//!       rep (i, 0, sz(nodes) - 1) {
//!         seen[nodes[i]] = 1;
//!         for (int v : adj[nodes[i]]) if (!seen[v]) {
//!           // edge nodes[i] <=> v is in current BCC
//!           count_edges++;
//!         }
//!       }
//!       if (count_edges == 1) {
//!         // nodes[0] <=> nodes[1] is a bridge
//!         return;
//!       }
//!       for (int v : nodes) uf.join(v, nodes[0]);
//!     });
//!     vector<basic_string<int>> bridge_tree(n);
//!     rep (i, 0, n)
//!       for (int v : adj[i])
//!         if (!uf.sameSet(i, v))
//!           bridge_tree[uf.find(i)] += uf.find(v);
//!   }
//!
//!   {
//!     // ********* IF NO MULTIPLE EDGES *********
//!     vector<vi> adj(n);
//!     vector<int> cc_id(n);
//!     bcc_callback(adj, [&](const vi& nodes) {
//!       if (sz(nodes) == 2) {
//!         // nodes[0] <=> nodes[1] is a bridge
//!         return;
//!       }
//!       for (int v : nodes) cc_id[v] = nodes.back();
//!     });
//!   }
//!
//!   vector<basic_string<int>> adj(n);
//!   vector<basic_string<int>> block_vertex_tree(2 * n);
//!   int bcc_id = n;
//!   bcc_callback(adj, [&](const vi& nodes) {
//!     for (int v : nodes) {
//!       block_vertex_tree[v] += bcc_id;
//!       block_vertex_tree[bcc_id] += v;
//!     }
//!     bcc_id++;
//!   });
//! @endcode
//! callback not called on components with a single node
//! @time O(n + m)
//! @space O(n)
void bcc_callback(const auto& adj, auto f) {
  int n = sz(adj), q = 0, s = 0;
  vi t(n), st(n);
  auto dfs = [&](auto&& self, int v) -> int {
    int l = t[v] = ++q;
    for (int u : adj[v]) {
      int siz = s, lu = 0;
      l = min(l, t[u] ?: (lu = self(self, st[s++] = u)));
      if (lu >= t[v]) {
        st[s++] = v;
        f({siz + all(st) - n + s});
        s = siz;
      }
    }
    return l;
  };
  rep(i, 0, n) if (!t[i]) dfs(dfs, i);
}
