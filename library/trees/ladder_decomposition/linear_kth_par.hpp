#pragma once
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
    int d, p = -1, dl, idx_j, idx_l;
  };
  vector<node> t;
  vector<pii> j;
  vi lad;
  linear_kth_par(const vector<vi>& adj):
    t(sz(adj)), j(2 * sz(t)) {
    vi st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] = {st[max(0, sz(st) - 1 - 2 * (pos & -pos))],
        st[max(0, sz(st) - 1 - 4 * (pos & -pos))]};
      pos++;
    };
    auto dfs = [&](auto&& self, int v) -> void {
      st.push_back(v);
      t[v].idx_j = pos, t[v].dl = v;
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
    rep(i, 0, sz(t)) {
      if (t[i].p == -1) dfs(dfs, i);
      if (t[i].p == -1 || t[t[i].p].dl != t[i].dl) {
        int v = t[i].dl, len = (t[v].d - t[i].d) * 2;
        t[v].idx_l = sz(lad) + t[v].d;
        for (; v != -1 && len--; v = t[v].p)
          lad.push_back(v);
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
      auto [j1, j2] = j[(t[v].idx_j & -i) | i];
      int up = t[v].d - t[j2].d <= k ? j2 : j1;
      return lad[t[t[up].dl].idx_l + k - t[v].d];
    }
  }
};
