//! @code
//!   RMQ rmq1(a, ranges::min);
//!   RMQ rmq2(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<RMQ<int, function<int(int, int)>>>
//!     rmqs(3, {{}, NULL});
//!   rmqs[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  RMQ(const vector<T>& a, F op): dp(1, a), op(op) {
    for (int i = 0; (2 << i) <= ssize(a); i++) {
      dp.emplace_back(ssize(a) - (2 << i) + 1);
      ranges::transform(dp[i], dp[i] | views::drop(1 << i),
        begin(dp[i + 1]), op);
    }
  }
  T query(int l, int r) { // [l, r)
    assert(l < r);
    int lg = __lg(r - l);
    return op(dp[lg][l], dp[lg][r - (1 << lg)]);
  }
};
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h
//! @code
//!   {
//!     vector<vi> adj(n);
//!     LCA lca(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   LCA lca(adj);
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
struct LCA {
  struct node {
    int in, sub_sz = 1, d, p = -1;
  };
  vector<node> t;
  RMQ<int, function<int(int, int)>> rmq = {{}, NULL};
  LCA(const auto& adj): t(ssize(adj)) {
    vector<int> order;
    auto dfs = [&](auto&& self, int v) -> void {
      t[v].in = ssize(order), order.push_back(v);
      for (int u : adj[v])
        if (u != t[v].p)
          t[u].d = t[t[u].p = v].d + 1, self(self, u),
          t[v].sub_sz += t[u].sub_sz;
    };
    for (int i = 0; i < ssize(t); i++)
      if (t[i].p == -1) dfs(dfs, i);
    rmq = {order, [&](int u, int v) {
             return t[u].d < t[v].d ? u : v;
           }};
  }
  int lca(int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(t[u].in, t[v].in);
    return t[rmq.query(x + 1, y + 1)].p;
  }
  int dist_edges(int u, int v) {
    return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
  }
  //! returns 1 if v is in u's subtree
  bool in_subtree(int u, int v) {
    return t[u].in <= t[v].in &&
      t[v].in < t[u].in + t[u].sub_sz;
  }
  //! returns 1 if w is on path from u to v
  bool on_path(int u, int v, int w) {
    return (in_subtree(w, u) || in_subtree(w, v)) &&
      in_subtree(lca(u, v), w);
  }
  //! https://codeforces.com/blog/entry/71567?#comment-559285
  //! returns the node
  //! vi({u,p[u],..,lca(u,v),..,p[v],v})[1]
  //! @time O(1)
  //! @space O(1)
  int next_on_path(int u, int v) {
    assert(u != v);
    return in_subtree(u, v)
      ? rmq.query(t[u].in + 1, t[v].in + 1)
      : t[u].p;
  }
  //! @code
  //!   vi le = mono_st(a, less());
  //!   // less_equal(), greater(), greater_equal()
  //! @endcode
  //! when cmp == less():
  //!   a[le[i]] < a[i]
  //! @time O(n)
  //! @space O(n)
  vector<int> mono_st(const auto& a, const auto& cmp) {
    vector<int> l(ssize(a));
    for (int i = 0; i < ssize(a); i++)
      for (l[i] = i - 1; l[i] >= 0 && !cmp(a[l[i]], a[i]);)
        l[i] = l[l[i]];
    return l;
  }
  //! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/CompressTree.h
  //! @code
  //!   vector<vi> adj(n);
  //!   LCA lca(adj);
  //!   auto [par, orig_node] =
  //!     lca.compress_tree(subset);
  //! @endcode
  //! par[i] = parent of i in compressed tree, par[0]==-1
  //! orig_node[i] = index of node in original tree
  //! @time O(|subset| log |subset|)
  //! @space O(|subset|)
  array<vector<int>, 2> compress_tree(vector<int> subset) {
    auto proj = [&](int v) { return t[v].in; };
    ranges::sort(subset, {}, proj);
    int siz = ssize(subset);
    for (int i = 1; i < siz; i++)
      subset.push_back(lca(subset[i - 1], subset[i]));
    ranges::sort(subset, {}, proj);
    subset.erase(unique(begin(subset), end(subset)),
      end(subset));
    return {
      mono_st(subset,
        [&](int u, int v) { return in_subtree(u, v); }),
      subset};
  }
};
