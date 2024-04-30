/** @file */
#pragma once
#include "../../data_structures/bit.hpp"
#include "sum_adjacent.hpp"
#include "edge_cd.hpp"
/**
 * @see https://judge.yosupo.jp/problem /vertex_add_range_contour_sum_on_tree
 */
template <class T> struct contour_range_query {
  int n;
  sum_adj<T> sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<BIT<T>, 2>> bits;
  /**
   * @param adj unrooted, undirected tree
   * @param a a[u] = initial number for node u
   * @time O(n log1.5 n)
   * @space O(n log1.5 n) for `info` and `bits`
   */
  contour_range_query(const vector<vi>& adj, const vector<T>& a) : n(sz(a)), sum_a(adj, a), info(n) {
    edge_cd(adj, [&](const vector<vi>& cd_adj, int cent, int split) {
      vector<vector<T>> sum_num(2, vector<T>(1));
      auto dfs = [&](auto&& self, int u, int p, int d, int side) -> void {
        info[u].push_back({sz(bits), d, side});
        if (sz(sum_num[side]) == d) sum_num[side].push_back(0);
        sum_num[side][d] += a[u];
        for (int v : cd_adj[u])
          if (v != p) self(self, v, u, 1 + d, side);
      };
      rep(i, 0, sz(cd_adj[cent]))
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
      bits.push_back({BIT<T>(sum_num[0]), BIT<T>(sum_num[1])});
    });
  }
  /**
   * @param u node
   * @param delta number to add to node u's number
   * @time O(log1.5(n) * log2(n))
   * @space O(1)
   */
  void update(int u, T delta) {
    sum_a.update(u, delta);
    for (auto [decomp, d, side] : info[u])
      bits[decomp][side].update(d, delta);
  }
  /**
   * @param u node
   * @param le,ri defines range [le, ri)
   * @returns sum of node v's number over all v such that le <= dist_edges(u, v) < ri
   * @time O(log1.5(n) * log2(n))
   * @space O(1)
   */
  T query(int u, int le, int ri) {
    assert(0 <= le && le <= ri && ri <= n);
    T sum = 0;
    if (le <= 0 && 0 < ri) sum += sum_a.sum[u];
    if (le <= 1 && 1 < ri) sum += sum_a.query(u);
    for (auto [decomp, d, side] : info[u]) {
      auto& bit = bits[decomp][!side];
      int my_l = clamp<int>(le - d, 1, sz(bit.s));
      int my_r = clamp<int>(ri - d, 1, sz(bit.s));
      sum += bit.query(my_l, my_r);
    }
    return sum;
  }
};
