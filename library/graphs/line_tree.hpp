#pragma once
#include "../../kactl/content/data-structures/UnionFind.h"
//! https://codeforces.com/blog/entry/71568?#comment-559304
//! @code
//!   sort(all(w_eds));
//!   auto [llist, uf] = line_tree(w_eds, n);
//!   for (int v = uf.find(0); v != -1;
//!     v = llist[v].first) {}
//! @endcode
//! llist[v] = {next node, edge weight}
//! uf.find(v) = head of linked list
//!   of component containing v
//! @time O(n + m * \alpha(n))
//! @space O(n + m)
pair<vector<pii>, UF> line_tree(
  const vector<array<int, 3>>& w_eds, int n) {
  vector<pii> list(n, {-1, -1});
  vi last(n);
  iota(all(last), 0);
  UF uf(n);
  for (auto [w, u, v] : w_eds) {
    u = uf.find(u), v = uf.find(v);
    if (uf.join(u, v)) {
      int p = uf.find(u);
      list[last[p]] = {p ^ u ^ v, w};
      last[p] = last[p ^ u ^ v];
    }
  }
  return {list, uf};
}
