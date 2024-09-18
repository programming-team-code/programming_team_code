//! @file
#pragma once
#include "linear_rmq.hpp"
//! @see https://codeforces.com/blog/entry/78898
//! @code{.cpp}
//!     auto [data, root, adj] = perm_tree(a);
//! @endcode
struct perm_tree {
  struct node {
    //! [mn_idx[v], mn_idx[v] + len[v]) is range of indexes
    //! [mn_num[v], mn_num[v] + len[v]) is range of numbers
    //! @{
    int mn_idx, mn_num, len;
    //! @}
    bool is_join;
  };
  vector<node> t;
  int root;
  vector<vi>
    adj; //!< [0, n) are leaves, [n, sz(adj)) are internal nodes
  bool touches(int u, int v) {
    return t[u].mn_num == t[v].mn_num + t[v].len ||
      t[v].mn_num == t[u].mn_num + t[u].len;
  }
  int allocate(int mn_i, int mn_v, int ln, bool join,
    const vi& ch) {
    t.push_back({mn_i, mn_v, ln, join});
    adj.push_back(ch);
    return sz(adj) - 1;
  }
  //! @param a permutation
  //! @time O(n)
  //! @space O(n)
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
          t[u].mn_num = min(t[u].mn_num, t[v].mn_num);
          t[u].len += t[v].len;
          adj[u].push_back(v);
          v = u;
          st.pop_back();
          continue;
        }
        if (touches(v, u)) {
          v = allocate(t[u].mn_idx,
            min(t[v].mn_num, t[u].mn_num),
            t[v].len + t[u].len, 1, {u, v});
          st.pop_back();
          continue;
        }
        int le = min(t[u].mn_idx, mn_i[t[v].mn_idx]),
            ri = max(i, mx_i[t[v].mn_idx]), idx = sz(st) - 1;
        while (ri == i && le != t[st[idx][0]].mn_idx)
          le = min(le, st[idx][1]), ri = max(ri, st[idx][2]),
          idx = st[idx][3];
        if (ri > i) {
          st.push_back({v, le, ri, idx});
          break;
        }
        int min_num = t[v].mn_num;
        vi ch(1 + sz(st) - idx, v);
        rep(j, idx, sz(st)) min_num =
          min(min_num, t[ch[j - idx] = st[j][0]].mn_num);
        v = allocate(le, min_num, i - le + 1, 0, ch);
        st.resize(idx);
      }
      if (empty(st)) st.push_back({v, -1, -1, -1});
    }
    assert(sz(st) == 1);
    root = st[0][0];
  }
};
