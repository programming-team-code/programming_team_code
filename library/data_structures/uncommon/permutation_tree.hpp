#pragma once
#include "linear_rmq.hpp"
//! https://codeforces.com/blog/entry/78898
//! @code
//!   auto [d, root, adj] = perm_tree(a);
//! @endcode
//! [d[v].mn_idx, d[v].mn_idx+d[v].len) index range
//! [d[v].mn_num, d[v].mn_num+d[v].len) number range
//! indexes [0, n) of adj are leaves
//! indexes [n, sz(adj)) of adj are internal nodes
//! @time O(n)
//! @space O(n)
struct perm_tree {
  struct node {
    int mn_idx, mn_num, len;
    bool is_join;
  };
  vector<node> d;
  int root;
  vector<vi> adj;
  bool touches(int u, int v) {
    return d[u].mn_num == d[v].mn_num + d[v].len ||
      d[v].mn_num == d[u].mn_num + d[u].len;
  }
  int allocate(int mn_i, int mn_v, int ln, bool join,
    const vi& ch) {
    d.push_back({mn_i, mn_v, ln, join});
    adj.push_back(ch);
    return sz(adj) - 1;
  }
  perm_tree(const vi& a) {
    int n = sz(a);
    vi mn_i(n), mx_i(n);
    {
      vi a_inv(n, -1);
      rep(i, 0, n) a_inv[a[i]] = i;
      linear_rmq rmq_min(a_inv, less());
      linear_rmq rmq_max(a_inv, greater());
      rep(i, 1, n) {
        mn_i[i] = a_inv[rmq_min.query_idx(a[i - 1], a[i])];
        mx_i[i] = a_inv[rmq_max.query_idx(a[i - 1], a[i])];
      }
    }
    rep(i, 0, n) allocate(i, a[i], 1, 0, {});
    vector<array<int, 4>> st;
    rep(i, 0, n) {
      int v = i;
      while (!empty(st)) {
        int u = st.back()[0];
        if (!empty(adj[u]) && touches(adj[u].back(), v)) {
          d[u].mn_num = min(d[u].mn_num, d[v].mn_num);
          d[u].len += d[v].len;
          adj[u].push_back(v);
          v = u;
          st.pop_back();
          continue;
        }
        if (touches(v, u)) {
          v = allocate(d[u].mn_idx,
            min(d[v].mn_num, d[u].mn_num),
            d[v].len + d[u].len, 1, {u, v});
          st.pop_back();
          continue;
        }
        int le = min(d[u].mn_idx, mn_i[d[v].mn_idx]),
            ri = max(i, mx_i[d[v].mn_idx]),
            idx = sz(st) - 1;
        while (ri == i && le != d[st[idx][0]].mn_idx)
          le = min(le, st[idx][1]),
          ri = max(ri, st[idx][2]), idx = st[idx][3];
        if (ri > i) {
          st.push_back({v, le, ri, idx});
          break;
        }
        int min_num = d[v].mn_num;
        vi ch(1 + sz(st) - idx, v);
        rep(j, idx, sz(st)) min_num =
          min(min_num, d[ch[j - idx] = st[j][0]].mn_num);
        v = allocate(le, min_num, i - le + 1, 0, ch);
        st.resize(idx);
      }
      if (empty(st)) st.push_back({v, -1, -1, -1});
    }
    assert(sz(st) == 1);
    root = st[0][0];
  }
};
