//! https://codeforces.com/blog/entry/71568?#comment-559304
//! @code
//!   ranges::sort(w_eds);
//!   line_tree lt(n);
//!   for (auto [w, u, v] : w_eds) lt.join(u, v);
//!   for (int v = lt.f(0); v != -1;) {
//!     auto [next, e_id] = lt.edge[v];
//!     int w = w_eds[e_id][0];
//!     //
//!     v = next;
//!   }
//! @endcode
//! lt.f(v) = head of linked list
//!   of component containing v
//! @time O(n + m * \alpha(n))
//! @space O(n + m)
struct line_tree {
  int id = 0;
  vector<int> p, last;
  vector<pair<int, int>> edge;
  line_tree(int n): p(n, -1), last(n), edge(n, {-1, -1}) {
    iota(begin(last), end(last), 0);
  }
  int size(int v) { return -p[f(v)]; }
  int f(int v) { return p[v] < 0 ? v : p[v] = f(p[v]); }
  bool join(int u, int v) {
    u = f(u), v = f(v), id++;
    if (u == v) return 0;
    if (p[u] < p[v]) swap(u, v);
    p[v] += p[u], p[u] = v;
    edge[last[v]] = {u, id - 1}, last[v] = last[u];
    return 1;
  }
};
