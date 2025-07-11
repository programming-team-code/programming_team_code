#pragma once
//! https://codeforces.com/blog/entry/125371
//! @code
//!   {
//!     vector<vi> adj(n);
//!     linear_lca llca(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   linear_lca llca(adj);
//! @endcode
//! @time O(n + q)
//! @space O(n)
struct linear_lca {
  struct node {
    int pos, label, asc;
  };
  vector<node> t;
  vi head;
  linear_lca(auto& adj) : t(sz(adj)), head(sz(t) + 1) {
    {
      int Time = 1;
      auto dfs = [&](auto&& self, int v, int p) -> void {
        t[v].label = Time++;
        for (int& u : adj[v]) {
          assert(u != p);
          self(self, u, v);
          head[t[u].label] = v;
          if ((t[u].label & -t[u].label) > (t[v].label & -t[v].label)) {
            t[v].label = t[u].label;
            swap(u, adj[v][0]);
          }
        }
      };
      dfs(dfs, 0, 0);
    }
    {
      int Time = 0;
      auto dfs = [&](auto&& self, int v, int p) -> void {
        t[v].asc = t[p].asc | (t[v].label & -t[v].label);
        t[v].pos = Time++;
        for (int u : adj[v])
          if (u != p) {
            self(self, u, v);
          }
      };
      dfs(dfs, 0, 0);
    }
  }
  int lca(int u, int v) {
    if (t[u].pos > t[v].pos) swap(u, v);
    if (unsigned j = t[u].label ^ t[v].label; j) {
      j = t[u].asc & t[v].asc & -bit_floor(j);
      //if (unsigned k = t[u].asc ^ j; k)
        //k = bit_floor(k), u = head[(t[u].label & -k) | k];
      if (unsigned k = t[v].asc ^ j; k)
        k = bit_floor(k), v = head[(t[v].label & -k) | k];
    }
    return t[u].pos < t[v].pos ? u : v;
  }
//#include "extra_members/dist_edges.hpp"
};
