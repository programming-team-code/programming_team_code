/** @file */
#pragma once
/**
 * @see Still Simpler Static Level Ancestors by Torben Hagerup, May 2020; https://codeforces.com/blog/entry/126580
 */
struct linear_kth_par {
  struct node {
    int d, p = -1, dl /*deepest leaf*/, idx;
    vi lad;
  };
  vector<node> t;
  vi j;
  /**
   * @code{.cpp}
             linear_kth_par kp(adj);
   * @endcode
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_kth_par(const vector<vi>& adj) : t(sz(adj)), j(2 * sz(t)) {
    vi st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] = st[max(0, sz(st) - 1 - 2 * (pos & -pos))];
      pos++;
    };
    auto dfs = [&](auto&& self, int u) -> void {
      st.push_back(u);
      t[u].idx = pos;
      t[u].dl = u;
      add_j();
      for (int v : adj[u])
        if (v != t[u].p) {
          t[v].d = t[t[v].p = u].d + 1;
          self(self, v);
          if (t[t[v].dl].d > t[t[u].dl].d) t[u].dl = t[v].dl;
          add_j();
        }
      st.pop_back();
    };
    rep(i, 0, sz(t)) if (t[i].p == -1) t[i].p = i, dfs(dfs, i);
    rep(i, 0, sz(t)) if (t[i].p == i || t[t[i].p].dl != t[i].dl) {
      int leaf = t[i].dl;
      vi& lad = t[leaf].lad;
      lad.resize(min((t[leaf].d - t[i].d) * 7 / 2, t[leaf].d + 1), leaf);
      rep(k, 1, sz(lad))
          lad[k] = t[lad[k - 1]].p;
    }
  }
  /**
   * @param u query node
   * @param k number of edges
   * @returns a node k edges up from u
   * @time O(1)
   * @space O(1)
   */
  int kth_par(int u, int k) {
    assert(0 <= k && k <= t[u].d);
    switch (k) {
      case 0: return u;
      case 1: return t[u].p;
      case 2: return t[t[u].p].p;
      default:
        int i = 1 << __lg(k / 3), leaf = t[j[(t[u].idx & -i) | i]].dl;
        return t[leaf].lad[k + t[leaf].d - t[u].d];
    }
  }
};
