#pragma once
#include "../../../kactl/content/data-structures/UnionFind.h"
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
      if (v != uf.find(v)) swap(u, v);
      list[last[v]] = {u, w};
      last[v] = last[u];
    }
  }
  return {list, uf};
}

struct line_tree {
  struct node {
    int p = -1, next = -1, w_next, last;
  };
  vi t;
  line_tree(int n) : t(n) {
    rep(i, 0, n) t[i].last = i;
  }
  int size(int x) { return -t[find(x)].p; }
  int find(int x) { return t[x].p < 0 ? x : t[x].p = find(t[x].p); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return 0;
    if (t[a].p > t[b].p) swap(a, b);
    t[a].p += t[b].p, t[b].p = a;
    return true;  // TODO add CI to check this is 1
  }
};
