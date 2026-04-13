#pragma once
//! https://codeforces.com/blog/entry/126580
//! @code
//!   vector<basic_string<int>> g(n);
//!   linear_kth_par kp(g);
//!   kp.kth_par(v, k); // k edges up from v
//!   kp.kth_par(v, 1); // v's parent
//! @endcode
//! @time O(n*max((2*KAPPA+3)/KAPPA,2*KAPPA) + q)
//! @space O(n*max((2*KAPPA+3)/KAPPA,2*KAPPA))
template<int KAPPA = 2> struct linear_kth_par {
  int n;
  vi d, leaf, pos, jmp;
  vector<vi> lad;
  linear_kth_par(const auto& g):
    n(sz(g)), d(n), leaf(n), pos(n), jmp(2 * n), lad(n) {
    static_assert(KAPPA >= 1);
    int t = 1;
    vi st(n);
    auto calc = [&](int s) {
      jmp[t] = st[max(0, s - KAPPA * (t & -t))];
      t++;
    };
    auto dfs = [&](auto dfs, int u, int p) -> void {
      int& l = leaf[u] = st[d[u]] = u;
      pos[u] = t;
      calc(d[u]);
      for (int v : g[u])
        if (v != p) {
          d[v] = 1 + d[u];
          dfs(dfs, v, u);
          if (d[l] < d[leaf[v]]) l = leaf[v];
          calc(d[u]);
        }
      int s = (d[l] - d[u]) * (2 * KAPPA + 3) / KAPPA;
      s = min(max(s, 2 * KAPPA), d[l] + 1);
      rep(i, sz(lad[l]), s) lad[l].push_back(st[d[l] - i]);
    };
    dfs(dfs, 0, 0);
  }
  int kth_par(int u, int k) {
    assert(0 <= k && k <= d[u]);
    int anc_d = d[u] - k;
    if (int j = bit_floor(k / (KAPPA + 1u)))
      u = jmp[(pos[u] & -j) | j];
    return u = leaf[u], lad[u][d[u] - anc_d];
  }
};
