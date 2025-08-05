#pragma once
//! https://codeforces.com/blog/entry/126580
//! @code
//!   {
//!     vector<vi> adj(n);
//!     linear_kth_par kp(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   linear_kth_par kp(adj);
//!   kp.kth_par(v, k); // k edges up from v
//!   kp.kth_par(v, 1); // v's parent
//! @endcode
//! @time O(n*max((2*KAPPA+3)/KAPPA,2*KAPPA) + q)
//! @space O(n*max((2*KAPPA+3)/KAPPA,2*KAPPA))
template<int KAPPA = 2> struct linear_kth_par {
  int n;
  vi d, leaf, pos, jmp;
  vector<vi> lad;
  linear_kth_par(const auto& adj):
    n(sz(adj)), d(n), leaf(n), pos(n), jmp(2 * n), lad(n) {
    static_assert(KAPPA >= 1);
    int t = 1;
    vi st(n);
    auto calc = [&](int s) {
      jmp[t] = st[max(0, s - KAPPA * (t & -t))];
      t++;
    };
    auto dfs = [&](auto&& self, int v, int p) -> void {
      st[d[v]] = v;
      int& l = leaf[v] = v;
      pos[v] = t;
      calc(d[v]);
      for (int u : adj[v])
        if (u != p) {
          d[u] = 1 + d[v];
          self(self, u, v);
          if (d[l] < d[leaf[u]]) l = leaf[u];
          calc(d[v]);
        }
      int s = (d[l] - d[v]) * (2 * KAPPA + 3) / KAPPA;
      s = min(max(s, 2 * KAPPA), d[l] + 1);
      rep(i, sz(lad[l]), s) lad[l].push_back(st[d[l] - i]);
    };
    dfs(dfs, 0, 0);
  }
  int kth_par(int v, int k) {
    assert(0 <= k && k <= d[v]);
    int j = v;
    if (unsigned b = k / (KAPPA + 1); b)
      b = bit_floor(b), j = jmp[(pos[v] & -b) | b];
    return j = leaf[j], lad[j][k + d[j] - d[v]];
  }
};
