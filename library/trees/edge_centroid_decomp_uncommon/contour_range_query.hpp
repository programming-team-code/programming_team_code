#pragma once
#include "../../data_structures/bit.hpp"
#include "sum_adjacent.hpp"
#include "../edge_cd.hpp"
//! https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree
struct contour_range_query {
  int n;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<BIT, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[v] = initial number for node v
  //! @time O(n log1.5 n)
  //! @space O(n log1.5 n) for `info` and `bits`
  contour_range_query(const vector<vi>& adj,
    const vector<ll>& a):
    n(sz(a)), sum_a(adj, a), info(n) {
    edge_cd(adj,
      [&](const vector<vi>& cd_adj, int cent, int split) {
        vector<vector<ll>> sum_num(2, vector<ll>(1));
        auto dfs = [&](auto&& self, int v, int p, int d,
                     int side) -> void {
          info[v].push_back({size(bits), d, side});
          if (sz(sum_num[side]) == d)
            sum_num[side].push_back(0);
          sum_num[side][d] += a[v];
          for (int u : cd_adj[v])
            if (u != p) self(self, u, v, 1 + d, side);
        };
        rep(i, 0, sz(cd_adj[cent]))
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
        bits.push_back({BIT(sum_num[0]), BIT(sum_num[1])});
      });
  }
  //! @param v node
  //! @param delta number to add to node v's number
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  void update(int v, ll delta) {
    sum_a.update(v, delta);
    for (auto [decomp, d, side] : info[v])
      bits[decomp][side].update(d, delta);
  }
  //! @param v node
  //! @param l,r defines range [l, r)
  //! @returns sum of node u's number over all u such that
  //! l
  //! <= dist_edges(u, v) < r
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  ll query(int v, int l, int r) {
    ll sum = 0;
    if (l <= 0 && 0 < r) sum += sum_a.sum[v];
    if (l <= 1 && 1 < r) sum += sum_a.query(v);
    for (auto [decomp, d, side] : info[v]) {
      auto& bit = bits[decomp][!side];
      int my_l = clamp<int>(l - d, 1, sz(bit.s));
      int my_r = clamp<int>(r - d, 1, sz(bit.s));
      sum += bit.query(my_l, my_r);
    }
    return sum;
  }
};
