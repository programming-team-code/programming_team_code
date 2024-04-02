/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/graph/cutpoints.html
 * @code{.cpp}
       vector<vector<pii>> adj(n);
       rep (i, 0, m) {
           int u, v;
           cin >> u >> v;
           u--, v--;
           adj[u].push_back({v, i});
           adj[v].push_back({u, i});
       }
       auto [num_bccs, is_cut, bcc_id] = cuts(adj, m);
 * @endcode
 */
struct cuts {
  int num_bccs = 0; /**< number of bi-connected components */
  vector<bool> is_cut; /**< is_cut[node] = 1 iff cut node */
  vi bcc_id; /**< bcc_id[edge id] = id of bcc (which are labeled 0, 1, ..., `num_bccs`-1) */
  /**
   * @param adj undirected graph; possibly with multiple edges; self edges not allowed
   * @param m number of edges
   * @time O(n + m)
   * @space this allocates member vectors which are O(n + m)
   */
  cuts(const vector<vector<pii>>& adj, int m) : is_cut(sz(adj)), bcc_id(m, -1) {
    int n = sz(adj), timer = 1;
    vi tin(n), st;
    auto dfs = [&](auto&& self, int u, int p_id) -> int {
      int low = tin[u] = timer++, deg = 0;
      for (auto [v, e_id] : adj[u]) {
        assert(u != v);
        if (e_id == p_id) continue;
        if (!tin[v]) {
          int siz = sz(st);
          st.push_back(e_id);
          int low_ch = self(self, v, e_id);
          if (low_ch >= tin[u]) {
            is_cut[u] = 1;
            rep(i, siz, sz(st))
                bcc_id[st[i]] = num_bccs;
            st.resize(siz);
            num_bccs++;
          }
          low = min(low, low_ch);
          deg++;
        } else if (tin[v] < tin[u]) {
          st.push_back(e_id);
          low = min(low, tin[v]);
        }
      }
      if (p_id == -1) is_cut[u] = (deg > 1);
      return low;
    };
    rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  }
};
