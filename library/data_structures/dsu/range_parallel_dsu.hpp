#pragma once
#include "../../../kactl/content/data-structures/UnionFind.h"
//! Given l1,l2,len, joins (l1,l2), (l1+1,l2+1),
//!   ..., (l1+len-1,l2+len-1)
//! `f` is called at most n-1 times
//! @time O(n*log(n)*α(n) + q)
//! @space O(n log n)
struct range_parallel_dsu {
  vector<UF> ufs;
  range_parallel_dsu(int n): ufs(__lg(n) + 1, UF(n)) {}
  template<class F>
  void join(int l1, int l2, int len, const F& f) {
    if (len == 0) return;
    int lg = __lg(len);
    join_impl(lg, l1, l2, f);
    join_impl(lg, l1 + len - (1 << lg), l2 + len - (1 << lg),
      f);
  }
  template<class F>
  void join_impl(int lvl, int u, int v, const F& f) {
    if (lvl == 0) {
      u = ufs[0].find(u);
      v = ufs[0].find(v);
      if (!ufs[0].join(v, u)) return;
      int w = ufs[0].find(u);
      return f(w, u ^ v ^ w);
    }
    if (!ufs[lvl].join(u, v)) return;
    join_impl(lvl - 1, u, v, f);
    join_impl(lvl - 1, u + (1 << (lvl - 1)),
      v + (1 << (lvl - 1)), f);
  }
};
