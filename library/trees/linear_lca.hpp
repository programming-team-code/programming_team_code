#pragma once
//! https://codeforces.com/blog/entry/125371
//! @time O(n + q)
//! @space O(n)
int lsb(int x) { return x & -x; }
struct linear_lca {
  struct node {
    int d, label, asc;
  };
  vector<node> t;
  vi head;
  linear_lca(const vector<vi>& adj):
    t(sz(adj)), head(sz(t) + 1) {
    vector<pii> order;
    auto dfs = [&](auto&& self, int v, int p) -> void {
      order.emplace_back(v, p);
      t[v].label = sz(order);
      for (int u : adj[v])
        if (u != p) {
          t[u].d = 1 + t[v].d;
          self(self, u, v);
          head[t[u].label] = v;
          if (lsb(t[u].label) > lsb(t[v].label))
            t[v].label = t[u].label;
        }
    };
    rep(i, 0, sz(t)) if (t[i].d == 0) dfs(dfs, i, i);
    for (auto [v, p] : order)
      t[v].asc = t[p].asc | lsb(t[v].label);
  }
  int lca(int u, int v) {
    if (int j = t[u].label ^ t[v].label; j) {
      j = t[u].asc & t[v].asc & -(1 << __lg(j));
      if (int k = t[u].asc ^ j; k)
        k = 1 << __lg(k), u = head[(t[u].label & -k) | k];
      if (int k = t[v].asc ^ j; k)
        k = 1 << __lg(k), v = head[(t[v].label & -k) | k];
    }
    return t[u].d < t[v].d ? u : v;
  }
#include "extra_members/dist_edges.hpp"
};
