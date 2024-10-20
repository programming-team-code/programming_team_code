#pragma once
#include "linear_rmq.hpp"
//! https://codeforces.com/blog/entry/78898
//! @code
//!   auto [p, root, ch] = perm_tree(a);
//! @endcode
//! [p[v].mn_idx, p[v].mn_idx+p[v].len) index range
//! [p[v].mn_num, p[v].mn_num+p[v].len) number range
//! indexes [0, n) of ch are leaves
//! indexes [n, sz(ch)) of ch are internal nodes
//! @time O(n)
//! @space O(n)
struct perm_tree {
  struct node {
    int mn_idx, mn_num, len;
    bool is_join;
  };
  vector<node> p;
  int root;
  vector<vi> ch;
  bool touches(int u, int v) {
    return p[u].mn_num == p[v].mn_num + p[v].len ||
      p[v].mn_num == p[u].mn_num + p[u].len;
  }
  int allocate(int mn_i, int mn_v, int ln, bool join,
    const vi& chs) {
    p.push_back({mn_i, mn_v, ln, join});
    ch.push_back(chs);
    return sz(ch) - 1;
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
        if (!empty(ch[u]) && touches(ch[u].back(), v)) {
          p[u].mn_num = min(p[u].mn_num, p[v].mn_num);
          p[u].len += p[v].len;
          ch[u].push_back(v);
          v = u;
          st.pop_back();
          continue;
        }
        if (touches(v, u)) {
          v = allocate(p[u].mn_idx,
            min(p[v].mn_num, p[u].mn_num),
            p[v].len + p[u].len, 1, {u, v});
          st.pop_back();
          continue;
        }
        int l = min(p[u].mn_idx, mn_i[p[v].mn_idx]),
            r = max(i, mx_i[p[v].mn_idx]),
            idx = sz(st) - 1;
        while (r == i && l != p[st[idx][0]].mn_idx)
          l = min(l, st[idx][1]), r = max(r, st[idx][2]),
          idx = st[idx][3];
        if (r > i) {
          st.push_back({v, l, r, idx});
          break;
        }
        int min_num = p[v].mn_num;
        vi chs(1 + sz(st) - idx, v);
        rep(j, idx, sz(st)) min_num =
          min(min_num, p[chs[j - idx] = st[j][0]].mn_num);
        v = allocate(l, min_num, i - l + 1, 0, chs);
        st.resize(idx);
      }
      if (empty(st)) st.push_back({v, -1, -1, -1});
    }
    assert(sz(st) == 1);
    root = st[0][0];
  }
};
