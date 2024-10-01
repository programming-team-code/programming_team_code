#pragma once
#include "../../kactl/content/data-structures/UnionFind.h"
pair<vector<pii>, UF> line_tree(
  const vector<array<int, 3>>& w_eds, int n) {
  vector<pii> list(n,
    {-1, -1}); // list[v] = {next node, edge weight}
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
