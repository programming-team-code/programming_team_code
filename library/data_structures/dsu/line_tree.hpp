#pragma once
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
struct line_tree {
  int id = 0;
  struct node {
    int p = -1, last;
    pii edge = {-1, -1};
  };
  vector<node> t;
  line_tree(int n): t(n) { rep(i, 0, n) t[i].last = i; }
  int size(int x) { return -t[find(x)].p; }
  int find(int x) {
    return t[x].p < 0 ? x : t[x].p = find(t[x].p);
  }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return 0;
    if (t[u].p < t[v].p) swap(u, v);
    t[v].p += t[u].p,
      t[u].p = v,
      t[exchange(t[v].last, t[u].last)].edge = {u, id++};
    return 1;
  }
};
