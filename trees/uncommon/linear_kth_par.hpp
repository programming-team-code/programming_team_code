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
  vector<int> d, d_tour, tin, idx, lad;
  vector<basic_string<int>> jmp;
  linear_kth_par(const auto& g): n(ssize(g)), d(n), d_tour(2 * n), tin(n), idx(n), lad(2 * n), jmp(2 * n) {
    int i = 0, t = 1;
    vector<int> st(n);
    auto calc = [&](int du) {
      for (int k = 1; k <= min(t & -t, du); k *= 2) jmp[t] += st[du - k];
      d_tour[t++] = du;
    };
    auto dfs = [&](auto dfs, int u, int p) -> vector<int> {
      vector<int> path;
      tin[st[d[u]] = u] = t;
      calc(d[u]);
      for (int v : g[u])
        if (v != p) {
          d[v] = d[u] + 1;
          vector<int> x = dfs(dfs, v, u);
          calc(d[u]);
          if (ssize(x) > ssize(path)) swap(x, path);
          for (int y : x) idx[y] = i;
          for (int y : x) lad[i++] = y;
          for (int k = 0; k < min<int>(ssize(x), d[v]); k++) lad[i++] = st[d[u] - k];
        }
      path.push_back(u);
      return path;
    };
    vector<int> x = dfs(dfs, 0, 0);
    for (int y : x) idx[y] = i;
    for (int y : x) lad[i++] = y;
  }
  int kth_par(int u, int k) {
    assert(0 <= k && k <= d[u]);
    if (k == 0) return u;
    int anc_d = d[u] - k, bc = bit_ceil(k + 0u);
    int t = (tin[u] + bc / 2) & -bc;
    int i = idx[jmp[t].at(__lg(d_tour[t] - anc_d))];
    return lad[i + d[lad[i]] - anc_d];
  }
};
