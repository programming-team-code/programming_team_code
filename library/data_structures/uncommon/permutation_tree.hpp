/** @file */
#pragma once
#include "linear_rmq.hpp"
/**
 * @see https://codeforces.com/blog/entry/78898
 * @code{.cpp}
       auto [is_join, mn_idx, mn_num, len, root, adj] = perm_tree(a);
 * @endcode
 */
struct perm_tree {
  vector<bool> is_join;
  /**
   * [mn_idx[u], mn_idx[u] + len[u]) is range of indexes
   * [mn_num[u], mn_num[u] + len[u]) is range of numbers
   * @{
   */
  vi mn_idx, mn_num, len;
  /** @} */
  int root;
  vector<vi> adj; /**< [0, n) are leaves, [n, sz(adj)) are internal nodes */
  bool touches(int u, int v) {
    return mn_num[u] == mn_num[v] + len[v] || mn_num[v] == mn_num[u] + len[u];
  }
  int allocate(bool join, int mn_i, int mn_v, int ln, const vi& ch) {
    is_join.push_back(join);
    mn_idx.push_back(mn_i);
    mn_num.push_back(mn_v);
    len.push_back(ln);
    adj.push_back(ch);
    return sz(adj) - 1;
  }
  /**
   * @param a permutation
   * @time O(n)
   * @space O(n)
   */
  perm_tree(const vi& a) {
    int n = sz(a);
    vi mn_i(n), mx_i(n);
    {
      vi a_inv(n, -1);
      rep(i, 0, n) {
        assert(0 <= a[i] && a[i] < n && a_inv[a[i]] == -1);
        a_inv[a[i]] = i;
      }
      linear_rmq rmq_min(a_inv, less());
      linear_rmq rmq_max(a_inv, greater());
      rep(i, 1, n) {
        mn_i[i] = a_inv[rmq_min.query_idx(a[i - 1], a[i])];
        mx_i[i] = a_inv[rmq_max.query_idx(a[i - 1], a[i])];
      }
    }
    rep(i, 0, n) allocate(0, i, a[i], 1, {});
    vector<array<int, 4>> st;
    rep(i, 0, n) {
      int u = i;
      while (!empty(st)) {
        int v = st.back()[0];
        if (!empty(adj[v]) && touches(adj[v].back(), u)) {
          mn_num[v] = min(mn_num[v], mn_num[u]);
          len[v] += len[u];
          adj[v].push_back(u);
          u = v;
          st.pop_back();
          continue;
        }
        if (touches(u, v)) {
          u = allocate(1, mn_idx[v], min(mn_num[u], mn_num[v]), len[u] + len[v], {v, u});
          st.pop_back();
          continue;
        }
        int le = min(mn_idx[v], mn_i[mn_idx[u]]), ri = max(i, mx_i[mn_idx[u]]), idx = sz(st) - 1;
        while (ri == i && le != mn_idx[st[idx][0]])
          le = min(le, st[idx][1]), ri = max(ri, st[idx][2]), idx = st[idx][3];
        if (ri > i) {
          st.push_back({u, le, ri, idx});
          break;
        }
        int min_num = mn_num[u];
        vi ch(1 + sz(st) - idx, u);
        rep(j, idx, sz(st))
            min_num = min(min_num, mn_num[ch[j - idx] = st[j][0]]);
        u = allocate(0, le, min_num, i - le + 1, ch);
        st.resize(idx);
      }
      if (empty(st)) st.push_back({u, -1, -1, -1});
    }
    assert(sz(st) == 1);
    root = st[0][0];
  }
};
