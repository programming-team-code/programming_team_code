//! https://codeforces.com/blog/entry/126580
//! @code
//!   linear_kth_par kp(adj);
//!   int kth_par = kp.kth_par(v, k);
//! @endcode
//! kth_par = a node k edges up from v
//! @time O(n + q)
//! @space O(n)
struct linear_kth_par {
  struct node {
    int d, p = -1, idx, dl;
    vector<int> lad;
  };
  vector<node> t;
  vector<pair<int, int>> j;
  linear_kth_par(const vector<vector<int>>& adj):
    t((int)size(adj)), j(2 * (int)size(t)) {
    vector<int> st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] = {
        st[max(0, (int)size(st) - 1 - 2 * (pos & -pos))],
        st[max(0, (int)size(st) - 1 - 4 * (pos & -pos))]};
      pos++;
    };
    auto dfs = [&](auto&& self, int v) -> void {
      st.push_back(v);
      t[v].idx = pos, t[v].dl = v;
      add_j();
      for (int u : adj[v])
        if (u != t[v].p) {
          t[u].d = t[t[u].p = v].d + 1;
          self(self, u);
          if (t[t[u].dl].d > t[t[v].dl].d)
            t[v].dl = t[u].dl;
          add_j();
        }
      st.pop_back();
    };
    for (int i = 0; i < ((int)size(t)); i++) {
      if (t[i].p == -1) dfs(dfs, i);
      if (t[i].p == -1 || t[t[i].p].dl != t[i].dl) {
        int leaf = t[i].dl;
        vector<int>& lad = t[leaf].lad;
        lad.resize(
          min((t[leaf].d - t[i].d) * 2, t[leaf].d + 1),
          leaf);
        for (int k = 1; k < ((int)size(lad)); k++)
          lad[k] = t[lad[k - 1]].p;
      }
    }
  }
  int kth_par(int v, int k) {
    assert(0 <= k && k <= t[v].d);
    switch (k) {
    case 0: return v;
    case 1: return t[v].p;
    case 2: return t[t[v].p].p;
    default:
      int i = 1 << __lg(k / 3);
      auto [j1, j2] = j[(t[v].idx & -i) | i];
      int leaf = t[t[v].d - t[j2].d <= k ? j2 : j1].dl;
      return t[leaf].lad[k + t[leaf].d - t[v].d];
    }
  }
};
