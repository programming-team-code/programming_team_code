/** @file */
#pragma once
inline int bit_floor(unsigned x) { return x ? 1 << __lg(x) : 0; }
/**
 * @see Still Simpler Static Level Ancestors by Torben Hagerup, May 2020; https://codeforces.com/blog/entry/126580
 */
struct linear_kth_par {
  int n;
  vi d, p, j, dl /*deepest leaf*/, idx;
  vector<vi> l_tbl;
  /**
   * @code{.cpp}
             linear_kth_par kp(adj);
             linear_kth_par<5> kp(adj);
   * @endcode
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_kth_par(const vector<vi>& adj) : n(sz(adj)), d(n), p(n, -1), dl(n), idx(n), l_tbl(n) {
    vi st;
    auto add_j = [&]() -> void {
      j.push_back(st[0]);
      int i = sz(st) - 1 - 2 * (sz(j) & -sz(j));
      if (i > 0) j.back() = st[i];
    };
    auto dfs = [&](auto&& self, int u) -> void {
      st.push_back(u);
      add_j();
      idx[u] = sz(j);
      dl[u] = u;
      for (int v : adj[u])
        if (v != p[u]) {
          d[v] = d[p[v] = u] + 1;
          self(self, v);
          add_j();
          if (d[dl[v]] > d[dl[u]]) dl[u] = dl[v];
        }
      st.pop_back();
    };
    rep(i, 0, n) if (p[i] == -1) p[i] = i, dfs(dfs, i);
    rep(i, 0, n) if (p[i] == i || dl[p[i]] != dl[i]) {
      int leaf = dl[i];
      vi& lad = l_tbl[leaf];
      lad.resize(min((d[leaf] - d[i]) * 7 / 2, d[leaf] + 1), leaf);
      rep(k, 1, sz(lad))
          lad[k] = p[lad[k - 1]];
    }
  }
  /**
   * @param u query node
   * @param k number of edges
   * @returns a node k edges up from u
   * @time O(1)
   * @space O(1)
   */
  inline int kth_par(int u, int k) {
    assert(0 <= k && k <= d[u]);
    if (k == 0) return u;
    if (k == 1) return p[u];
    if (k == 2) return p[p[u]];
    int i = bit_floor(unsigned(k / 3)), leaf = dl[j[((idx[u] & -i) | i) - 1]];
    return l_tbl[leaf][k + d[leaf] - d[u]];
  }
};
