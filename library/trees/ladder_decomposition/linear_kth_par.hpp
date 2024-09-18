#pragma once
//! Still Simpler Static Level Ancestors by Torben Hagerup,
//! May 2020; https://codeforces.com/blog/entry/126580
struct linear_kth_par {
  struct node {
    int d, p = -1, idx, dl; //!< deepest leaf
    vi lad;
  };
  vector<node> t;
  vi j;
  //! @code
  //!         linear_kth_par kp(adj);
  //! @endcode
  //! @param adj forest (rooted or unrooted)
  //! @time O(n)
  //! @space O(n)
  linear_kth_par(const vector<vi>& adj):
    t(sz(adj)), j(2 * sz(t)) {
    vi st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] = st[max(0, sz(st) - 1 - 2 * (pos & -pos))];
      pos++;
    };
    auto dfs = [&](auto&& self, int v) -> void {
      st.push_back(v);
      t[v].idx = pos;
      t[v].dl = v;
      add_j();
      for (int u : adj[v])
        if (u != t[v].p) {
          t[u].d = t[t[u].p = v].d + 1;
          self(self, u);
          if (t[t[u].dl].d > t[t[v].dl].d) t[v].dl = t[u].dl;
          add_j();
        }
      st.pop_back();
    };
    rep(i, 0, sz(t)) if (t[i].p == -1) t[i].p = i,
                                       dfs(dfs, i);
    rep(i, 0, sz(t)) if (
      t[i].p == i || t[t[i].p].dl != t[i].dl) {
      int leaf = t[i].dl;
      vi& lad = t[leaf].lad;
      lad.resize(
        min((t[leaf].d - t[i].d) * 7 / 2, t[leaf].d + 1),
        leaf);
      rep(k, 1, sz(lad)) lad[k] = t[lad[k - 1]].p;
    }
  }
  //! @param v query node
  //! @param k number of edges
  //! @returns a node k edges up from v
  //! @time O(1)
  //! @space O(1)
  int kth_par(int v, int k) {
    switch (k) {
    case 0: return v;
    case 1: return t[v].p;
    case 2: return t[t[v].p].p;
    default:
      int i = 1 << __lg(k / 3),
          leaf = t[j[(t[v].idx & -i) | i]].dl;
      return t[leaf].lad[k + t[leaf].d - t[v].d];
    }
  }
};
