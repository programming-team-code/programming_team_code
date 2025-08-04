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
//! @time O(n*(2*KAPPA+1)/(KAPPA-1) + n*2*(KAPPA-1) + q)
//! @space O(n*(2*KAPPA+1)/(KAPPA-1) + n*2*(KAPPA-1))
template<int KAPPA = 3> struct linear_kth_par {
  int n;
  vi d, leaf, pos, jmp;
  vector<basic_string<int>> lad;
  linear_kth_par(const auto& adj):
    n(sz(adj)), d(n), leaf(n), pos(n), jmp(2 * n), lad(n) {
    static_assert(KAPPA >= 2);
    int t = 1;
    vi st(n);
    auto calc = [&](int siz) {
      jmp[t] = st[max(0, siz - (KAPPA - 1) * (t & -t))];
      t++;
    };
    auto dfs = [&](auto&& self, int v, int p) -> void {
      st[d[v]] = leaf[v] = v;
      pos[v] = t;
      calc(d[v]);
      for (int u : adj[v])
        if (u != p) {
          d[u] = 1 + d[v];
          self(self, u, v);
          if (d[leaf[v]] < d[leaf[u]]) leaf[v] = leaf[u];
          calc(d[v]);
        }
      // TODO golf this further
      int len = (d[leaf[v]] - d[v]) * (2 * KAPPA + 1) /
        (KAPPA - 1);
      len = max(len, 2 * (KAPPA - 1));
      int i = d[leaf[v]] - sz(lad[leaf[v]]);
      while (i && sz(lad[leaf[v]]) < len)
        lad[leaf[v]] += st[i--];
      assert(lad[leaf[v]].back() > 0);
    };
    dfs(dfs, 0, 0);
  }
  int kth_par(int v, int k) {
    assert(0 <= k && k <= d[v]);
    int j = v;
    if (unsigned b = k / KAPPA; b)
      b = bit_floor(b), j = jmp[(pos[v] & -b) | b];
    // TODO array index out of bounds goes uncaught here
    // because of basic_string
    return j = leaf[j], lad[j][k + d[j] - d[v]];
  }
};
