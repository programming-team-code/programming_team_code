#pragma once
#include "../../data_structures_[l,r)/bit.hpp"
#include "../edge_cd.hpp"
#include "sum_adjacent.hpp"
//! https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree
struct contour_range_query {
  int n;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<BIT, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[u] = initial number for node u
  //! @time O(n logφ n)
  //! @space O(n logφ n) for `info` and `bits`
  contour_range_query(const vector<vi>& adj,
    const vector<ll>& a):
    n(sz(a)), sum_a(adj, a), info(n) {
    edge_cd(adj,
      [&](const vector<vi>& cd_adj, int cent, int split) {
        vector<vector<ll>> sum_num(2, vector<ll>(1));
        auto dfs = [&](auto&& self, int u, int p, int d,
                     int side) -> void {
          info[u].push_back({int(sz(bits)), d, side});
          if (sz(sum_num[side]) == d)
            sum_num[side].push_back(0);
          sum_num[side][d] += a[u];
          for (int c : cd_adj[u])
            if (c != p) self(self, c, u, 1 + d, side);
        };
        rep(i, 0, sz(cd_adj[cent]))
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
        bits.push_back({BIT(sum_num[0]), BIT(sum_num[1])});
      });
  }
  //! @param u node
  //! @param delta number to add to node u's number
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  void update(int u, ll delta) {
    sum_a.update(u, delta);
    for (auto [decomp, d, side] : info[u])
      bits[decomp][side].update(d, delta);
  }
  //! @param u node
  //! @param l,r defines range [l, r)
  //! @returns sum of node v's number over all v such that
  //! l <= dist(u, v) < r
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  ll query(int u, int l, int r) {
    ll sum = 0;
    if (l <= 0 && 0 < r) sum += sum_a.sum[u];
    if (l <= 1 && 1 < r) sum += sum_a.query(u);
    for (auto [decomp, d, side] : info[u]) {
      auto& bit = bits[decomp][!side];
      int my_l = clamp<int>(l - d, 1, sz(bit.s));
      int my_r = clamp<int>(r - d, 1, sz(bit.s));
      sum += bit.query(my_l, my_r);
    }
    return sum;
  }
};
