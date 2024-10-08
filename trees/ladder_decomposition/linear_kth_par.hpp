//! https://codeforces.com/blog/entry/126580
//! @code
//!   linear_kth_par kp(adj);
//!   int kth_par = kp.kth_par(v, k);
//! @endcode
//! kth_par = a node k edges up from v
//! @time O(3.5*n + q)
//! @space O(3.5*n)
struct linear_kth_par {
  struct node {
    int d, p = -1, idx, dl;
    vector<int> lad;
  };
  vector<node> t;
  vector<int> j;
  linear_kth_par(const vector<vector<int>>& adj):
    t((int)size(adj)), j(2 * (int)size(t)) {
    vector<int> st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] =
        st[max(0, (int)size(st) - 1 - 2 * (pos & -pos))];
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
          if (t[t[u].dl].d > t[t[v].dl].d)
            t[v].dl = t[u].dl;
          add_j();
        }
      st.pop_back();
    };
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].p == -1) t[i].p = i, dfs(dfs, i);
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].p == i || t[t[i].p].dl != t[i].dl) {
        int leaf = t[i].dl;
        vector<int>& lad = t[leaf].lad;
        lad.resize(
          min((t[leaf].d - t[i].d) * 7 / 2, t[leaf].d + 1),
          leaf);
        for (int k = 1; k < ((int)size(lad)); k++)
          lad[k] = t[lad[k - 1]].p;
      }
  }
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
