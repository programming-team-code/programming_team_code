#pragma once
#include "dsu.hpp"
//! Given l1,l2,len; joins (l1,l2), (l1+1,l2+1),
//!   ..., (l1+len-1,l2+len-1)
//! `f` is called at most n-1 times
//! @time O(n*log(n)*\alpha(n) + q)
//! @space O(n log n)
struct rp_dsu {
  vector<DSU> dsus;
  rp_dsu(int n): dsus(bit_width(unsigned(n)), DSU(n)) {}
  void join(int l1, int l2, int len, const auto& f) {
    if (len == 0) return;
    int lg = __lg(len);
    join_impl(lg, l1, l2, f);
    join_impl(lg, l1 + len - (1 << lg),
      l2 + len - (1 << lg), f);
  }
  void join_impl(int lvl, int u, int v, const auto& f) {
    if (lvl == 0) {
      u = dsus[0].f(u);
      v = dsus[0].f(v);
      if (!dsus[0].join(v, u)) return;
      int w = dsus[0].f(u);
      return f(w, u ^ v ^ w);
    }
    if (!dsus[lvl].join(u, v)) return;
    join_impl(lvl - 1, u, v, f);
    join_impl(lvl - 1, u + (1 << (lvl - 1)),
      v + (1 << (lvl - 1)), f);
  }
};
