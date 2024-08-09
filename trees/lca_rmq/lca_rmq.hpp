/**
 * @code{.cpp}
       vector<ll> a;
       vi le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp transitive compare operator
 * @returns vector le where le[i] = max index such that: le[i] < i and
 *          cmp(a[le[i]], a[i]). If no index exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1; le[i] >= 0 && !cmp(a[le[i]], a[i]);) le[i] = le[le[i]];
  return le;
}
/**
 * @code{.cpp}
       vector<ll> a;
       RMQ rmq(a, ranges::min); // -std=c++20
       RMQ rmq(a, [&](auto& x, auto& y) { return min(x, y); });
 * @endcode
 */
template <class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  /**
   * @param a static array
   * @param a_op any associative, commutative, idempotent operation
   * @time O(n log n)
   * @space O(n log n) for `dp` vector
   */
  RMQ(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= (int)size(a); i++) {
      dp.emplace_back((int)size(a) - (2 << i) + 1);
      transform(begin(dp[i]), end(dp[i]) - (1 << i), begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns a[le] op a[le + 1] op ... op a[ri - 1]
   * @time O(1)
   * @space O(1)
   */
  T query(int le, int ri) {
    assert(le < ri);
    int lg = __lg(ri - le);
    return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
  }
};
/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/LCA.h
 */
struct LCA {
  struct node {
    int in, sub_sz = 1, d, p = -1;
  };
  vector<node> t;
  RMQ<int, function<int(int, int)>> rmq = {{}, nullptr};
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n log n)
   * @space O(n log n) for rmq, all other vectors are O(n)
   */
  LCA(const vector<vector<int>>& adj) : t((int)size(adj)) {
    vector<int> order;
    auto dfs = [&](auto&& self, int v) -> void {
      t[v].in = (int)size(order), order.push_back(v);
      for (int u : adj[v])
        if (u != t[v].p)
          t[u].d = t[t[u].p = v].d + 1, self(self, u), t[v].sub_sz += t[u].sub_sz;
    };
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].p == -1) dfs(dfs, i);
    rmq = {order, [&](int v, int u) { return t[v].d < t[u].d ? v : u; }};
  }
  /**
   * @param u,v 2 nodes in the same component
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  int lca(int v, int u) {
    if (v == u) return v;
    auto [x, y] = minmax(t[v].in, t[u].in);
    return t[rmq.query(x + 1, y + 1)].p;
  }
  /**
   * @param u,v endpoint nodes of path
   * @returns number of edges on path
   * @time same as lca(u, v)
   * @space O(1)
   */
  int dist_edges(int u, int v) {
    return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
  }
  /**
   * @param u,v 2 nodes
   * @returns 1 iff v is in u's subtree
   * @time O(1)
   * @space O(1)
   */
  bool in_subtree(int u, int v) {
    return t[u].in <= t[v].in && t[v].in < t[u].in + t[u].sub_sz;
  }
  /**
   * @see https://codeforces.com/blog/entry/71567?#comment-559285
   * @code{.cpp}
         LCA lc(adj);
         int u, v; //to loop over all nodes (except v) on path from u to v:
         for (int i = u; i != v; i = lc.next_on_path(i, v)) {}
   * @endcode
   * @param u,v endpoint nodes of path
   * @returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[1]
   * @time O(1)
   * @space O(1)
   */
  int next_on_path(int u, int v) {
    return in_subtree(u, v) ? rmq.query(t[u].in + 1, t[v].in + 1) : t[u].p;
  }
  /**
   * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/CompressTree.h
   *
   * Given a rooted tree and a subset S of nodes, compute the minimal subtree
   * that contains all the nodes by adding all (at most |S|-1) pairwise LCA's and
   * compressing edges.
   *
   * @code{.cpp}
         auto [par, orig_node] = lin_lca.compress_tree(subset);
   * @endcode
   *
   * @param subset subset of nodes
   * @returns vectors `par`, `orig_node`, for node i in compressed tree:
   *          par[i] = parent of i in compressed tree; par[0] == -1; par[i] < i
   *          orig_node[i] = corresponding node in big tree
   * @time O(k log k); k = sz(subset)
   * @space O(k) vectors are allocated and returned
   */
  array<vector<int>, 2> compress_tree(vector<int> subset) {
    auto cmp = [&](int u, int v) { return t[u].in < t[v].in; };
    sort(begin(subset), end(subset), cmp);
    int siz = (int)size(subset);
    for (int i = 1; i < (siz); i++)
      subset.push_back(lca(subset[i - 1], subset[i]));
    sort(begin(subset), end(subset), cmp);
    subset.erase(unique(begin(subset), end(subset)), end(subset));
    return {mono_st(subset, [&](int u, int v) { return in_subtree(u, v); }), subset};
  }
};
