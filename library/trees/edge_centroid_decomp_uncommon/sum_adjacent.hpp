#pragma once
//! helper for edge CD: given tree, update node's number,
//! find sum of neighbors' numbers
struct sum_adj {
  int n;
  vector<ll> sum, sum_ch;
  vi p;
  //! @param adj undirected, unrooted tree
  //! @param a_sum a_sum[v] = initial number for node v
  //! @time O(n)
  //! @space various O(n) vectors are allocated; recursion
  //! stack for dfs is O(n)
  sum_adj(const vector<vi>& adj, const vector<ll>& a_sum):
    n(sz(a_sum)), sum(a_sum), sum_ch(n), p(n, -1) {
    auto dfs = [&](auto&& self, int v) -> void {
      for (int u : adj[v])
        if (u != p[v])
          p[u] = v, sum_ch[v] += sum[u], self(self, u);
    };
    dfs(dfs, 0);
  }
  //! @param v node
  //! @param delta number to add
  //! @time O(1)
  //! @space O(1)
  void update(int v, ll delta) {
    sum[v] += delta;
    if (p[v] != -1) sum_ch[p[v]] += delta;
  }
  //! @param v node
  //! @returns sum of v's neighbors numbers
  //! @time O(1)
  //! @space O(1)
  ll query(int v) {
    return sum_ch[v] + (p[v] != -1 ? sum[p[v]] : 0);
  }
};
