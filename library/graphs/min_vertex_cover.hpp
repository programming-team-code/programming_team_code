#include "../../kactl/content/graph/HopcroftKarp.h"
//! @code
//!   int l_sz, r_sz;
//!   vector<vi> g(l_sz);
//!   g[u].push_back(v); // 0 <= u < l_sz, 0 <= v < r_sz
//!   vi r(r_sz, -1);
//!   int match_sz = hopcroftKarp(g, r);
//!   // r[v] != -1 iff edge r[v] <-> v in matching
//!   auto [mvc_l, mvc_r] = cover(g, r);
//!   // mvc_l[u] == 1 iff u in mvc
//! @endcode
//! @time O(n + q * log n)
//! @space O(n * \alpha(n))
pair<vi, vi> cover(const vector<vi>& g, vi& r) {
  int n = sz(g), t = 0;
  vi cl(n), cr(sz(r)), q(n);
  for (int u : r)
    if (u != -1) cl[u] = 1;
  rep(i, 0, n) if (!cl[i]) q[t++] = i;
  rep(i, 0, t) for (int v : g[q[i]]) {
    cr[v] = 1;
    if (r[v] != -1 && cl[r[v]]) cl[q[t++] = r[v]] = 0;
  }
  return {cl, cr};
}
