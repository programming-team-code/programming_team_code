#pragma once
#include "dsu.hpp"
//! Given u,v,len; joins (u,v), (u+1,v+1),
//!   ..., (u+len-1,v+len-1)
//! `f` is called at most n-1 times
//! @time O(n*log(n)*\alpha(n) + q)
//! @space O(n log n)
struct rp_dsu {
  vector<DSU> dsus;
  rp_dsu(int n): dsus(bit_width(unsigned(n)), DSU(n)) {}
  void join(int u, int v, int len, const auto& f) {
    int i = __lg(len);
    join(u, v, f, i);
    join(u + len - (1 << i), v + len - (1 << i), f, i);
  }
  void join(int u, int v, const auto& f, int i) {
    if (i == 0) {
      u = dsus[0].f(u);
      v = dsus[0].f(v);
      if (!dsus[0].join(v, u)) return;
      int w = dsus[0].f(u);
      return f(w, u ^ v ^ w);
    }
    if (!dsus[i].join(u, v)) return;
    join(u, v, f, i - 1);
    join(u + (1 << (i - 1)), v + (1 << (i - 1)), f, i - 1);
  }
};
