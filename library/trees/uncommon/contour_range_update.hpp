#pragma once
#include "../../data_structures_[l,r)/bit_uncommon/rupq.hpp"
#include "../edge_cd.hpp"
#include "sum_adjacent.hpp"
//! https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
struct contour_range_update {
  int n;
  vector<ll> a;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<bit_rupq, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[u] = initial number for node u
  //! @time O(n logφ n)
  //! @space O(n logφ n) for `info` and `bits`
  contour_range_update(const vector<vi>& adj,
    const vector<ll>& a):
    n(sz(a)), a(a), sum_a(adj, vector<ll>(n)), info(n) {
    edge_cd(adj,
      [&](const vector<vi>& cd_adj, int cent, int split) {
        array<int, 2> mx_d = {0, 0};
        auto dfs = [&](auto&& self, int u, int p, int d,
                     int side) -> void {
          mx_d[side] = max(mx_d[side], d);
          info[u].push_back({int(sz(bits)), d, side});
          for (int v : cd_adj[u])
            if (v != p) self(self, v, u, 1 + d, side);
        };
        rep(i, 0, sz(cd_adj[cent]))
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
        bits.push_back(
          {bit_rupq(mx_d[0] + 1), bit_rupq(mx_d[1] + 1)});
      });
  }
  //! @param u,l,r,delta add delta to all nodes v such
  //! that l <= dist(u, v) < r
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  void update(int u, int l, int r, ll delta) {
    if (l <= 0 && 0 < r) a[u] += delta;
    if (l <= 1 && 1 < r) sum_a.update(u, delta);
    for (auto [decomp_id, d, side] : info[u]) {
      auto& bit = bits[decomp_id][!side];
      int my_l = clamp<int>(l - d, 1, bit.n);
      int my_r = clamp<int>(r - d, 1, bit.n);
      bit.update(my_l, my_r, delta);
    }
  }
  //! @param u node
  //! @returns number of node u
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  ll query(int u) {
    ll sum = a[u] + sum_a.query(u);
    for (auto [decomp_id, d, side] : info[u])
      sum += bits[decomp_id][side].get_index(d);
    return sum;
  }
};
