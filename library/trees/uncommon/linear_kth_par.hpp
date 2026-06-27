#pragma once
//! https://link.springer.com/chapter/10.1007/978-3-032-29003-8_29
//! https://codeforces.com/blog/entry/153250
//! @code
//!   vector<basic_string<int>> g(n);
//!   linear_kth_par kp(g);
//!   kp.kth_par(v, k); // k edges up from v
//!   kp.kth_par(v, 1); // v's parent
//! @endcode
//! @time O(n + q)
//! @space O(n)
struct linear_kth_par {
  int n;
  vi d, et_i, et_d, idx, lad;
  vector<basic_string<int>> jmp;
  linear_kth_par(const auto& g):
    n(sz(g)), d(n), et_i(n), et_d(2 * n), idx(n),
    lad(2 * n), jmp(2 * n) {
    int i = 0, j = 1;
    vi st(n);
    auto calc = [&](int u) {
      et_d[et_i[u] = j] = d[u];
      for (int k = 1; k <= min(j & -j, d[u]); k *= 2)
        jmp[j] += st[d[u] - k];
      j++;
    };
    auto dfs = [&](auto dfs, int u, int p) -> vi {
      vi path;
      st[d[u]] = u;
      calc(u);
      for (int v : g[u])
        if (v != p) {
          d[v] = d[u] + 1;
          vi x = dfs(dfs, v, u);
          calc(u);
          if (sz(x) > sz(path)) swap(x, path);
          for (int y : x) idx[y] = i;
          for (int y : x) lad[i++] = y;
          rep(k, 0, min<int>(sz(x), d[v]))
            lad[i++] = st[d[u] - k];
        }
      path.push_back(u);
      return path;
    };
    vi x = dfs(dfs, 0, 0);
    for (int y : x) idx[y] = i;
    for (int y : x) lad[i++] = y;
  }
  int kth_par(int u, int k) {
    assert(0 <= k && k <= d[u]);
    if (k == 0) return u;
    int anc_d = d[u] - k, bc = bit_ceil(k + 0u);
    int j = (et_i[u] + bc / 2) & -bc;
    int i = idx[jmp[j].at(__lg(et_d[j] - anc_d))];
    return lad[i + d[lad[i]] - anc_d];
  }
};
