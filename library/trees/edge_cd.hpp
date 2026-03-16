#pragma once
//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://codeforces.com/blog/entry/142176
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   vector<basic_string<int>> adj(n);
//!   edge_cd(adj, [&](int cent, int m) {
//!     // subtrees of [0, m) of adj[cent]: 1st edge-set
//!     // subtrees of [m, sz(adj[cent])): 2nd edge-set
//!   });
//! @endcode
//! handle single-edge-paths separately
//! @time O(n logφ n)
//! @space O(n)
template<class G>
void edge_cd(vector<G>& adj, const auto& f) {
  vi siz(sz(adj));
  auto find_cent = [&](auto&& self, int u, int p,
                     int m) -> int {
    siz[u] = 1;
    for (int v : adj[u])
      if (v != p) {
        int cent = self(self, v, u, m);
        if (cent != -1) return cent;
        siz[u] += siz[v];
      }
    return 2 * siz[u] > m
           ? p >= 0 && (siz[p] = m + 1 - siz[u]),
           u : -1;
  };
  auto dfs = [&](auto&& self, int u, int m) -> void {
    if (m < 2) return;
    u = find_cent(find_cent, u, -1, m);
    int sum = 0;
    auto it = partition(all(adj[u]), [&](int v) {
      ll x = sum + siz[v];
      return x * x < m * (m - x) ? sum += siz[v], 1 : 0;
    });
    f(u, it - begin(adj[u]));
    G oth(it, end(adj[u]));
    adj[u].erase(it, end(adj[u]));
    self(self, u, sum);
    swap(adj[u], oth);
    self(self, u, m - sum);
  };
  dfs(dfs, 0, sz(adj) - 1);
};
