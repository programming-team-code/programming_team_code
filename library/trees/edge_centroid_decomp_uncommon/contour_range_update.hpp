#pragma once
#include "../../data_structures/bit_uncommon/rupq.hpp"
#include "sum_adjacent.hpp"
#include "../edge_cd.hpp"
//! https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
struct contour_range_update {
  int n;
  vector<ll> a;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<bit_rupq, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[v] = initial number for node v
  //! @time O(n log1.5 n)
  //! @space O(n log1.5 n) for `info` and `bits`
  contour_range_update(const vector<vi>& adj,
    const vector<ll>& a):
    n(sz(a)), a(a), sum_a(adj, vector<ll>(n)), info(n) {
    edge_cd(adj,
      [&](const vector<vi>& cd_adj, int cent, int split) {
        array<int, 2> mx_d = {0, 0};
        auto dfs = [&](auto&& self, int v, int p, int d,
                     int side) -> void {
          mx_d[side] = max(mx_d[side], d);
          info[v].push_back({int(sz(bits)), d, side});
          for (int u : cd_adj[v])
            if (u != p) self(self, u, v, 1 + d, side);
        };
        rep(i, 0, sz(cd_adj[cent]))
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
        bits.push_back(
          {bit_rupq(mx_d[0] + 1), bit_rupq(mx_d[1] + 1)});
      });
  }
  //! @param v,l,r,delta add delta to all nodes u such
  //! that l <= dist_edges(v, u) < r
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  void update(int v, int l, int r, ll delta) {
    if (l <= 0 && 0 < r) a[v] += delta;
    if (l <= 1 && 1 < r) sum_a.update(v, delta);
    for (auto [decomp_id, d, side] : info[v]) {
      auto& bit = bits[decomp_id][!side];
      int my_l = clamp<int>(l - d, 1, bit.n);
      int my_r = clamp<int>(r - d, 1, bit.n);
      bit.update(my_l, my_r, delta);
    }
  }
  //! @param v node
  //! @returns number of node v
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  ll query(int v) {
    ll sum = a[v] + sum_a.query(v);
    for (auto [decomp_id, d, side] : info[v])
      sum += bits[decomp_id][side].get_index(d);
    return sum;
  }
};
