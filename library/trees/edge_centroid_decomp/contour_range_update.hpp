//! @file
#pragma once
#include "../../data_structures/bit_uncommon/rupq.hpp"
#include "sum_adjacent.hpp"
#include "edge_cd.hpp"
//! @see https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
template <class T> struct contour_range_update {
  int n;
  vector<T> a;
  sum_adj<T> sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<bit_rupq<T>, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a_a a_a[v] = initial number for node v
  //! @time O(n log1.5 n)
  //! @space O(n log1.5 n) for `info` and `bits`
  contour_range_update(const vector<vi>& adj, const vector<T>& a_a) : n(sz(a_a)), a(a_a), sum_a(adj, vector<T>(n)), info(n) {
    edge_cd(adj, [&](const vector<vi>& cd_adj, int cent, int split) {
      array<int, 2> mx_d = {0, 0};
      auto dfs = [&](auto&& self, int v, int p, int d, int side) -> void {
        mx_d[side] = max(mx_d[side], d);
        info[v].push_back({sz(bits), d, side});
        for (int u : cd_adj[v])
          if (u != p) self(self, u, v, 1 + d, side);
      };
      rep(i, 0, sz(cd_adj[cent]))
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
      bits.push_back({bit_rupq<T>(mx_d[0] + 1), bit_rupq<T>(mx_d[1] + 1)});
    });
  }
  //! @param v,le,ri,delta add delta to all nodes u such that le <= dist_edges(v, u) < ri
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  void update(int v, int le, int ri, T delta) {
    if (le <= 0 && 0 < ri) a[v] += delta;
    if (le <= 1 && 1 < ri) sum_a.update(v, delta);
    for (auto [decomp_id, d, side] : info[v]) {
      auto& bit = bits[decomp_id][!side];
      int my_l = clamp<int>(le - d, 1, bit.n);
      int my_r = clamp<int>(ri - d, 1, bit.n);
      bit.update(my_l, my_r, delta);
    }
  }
  //! @param v node
  //! @returns number of node v
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  T query(int v) {
    T sum = a[v] + sum_a.query(v);
    for (auto [decomp_id, d, side] : info[v])
      sum += bits[decomp_id][side].get_index(d);
    return sum;
  }
};
