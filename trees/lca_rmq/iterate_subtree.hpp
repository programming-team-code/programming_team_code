/**
 * @code{.cpp}
       vector<int64_t> a;
       vector<int> le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp transitive compare operator
 * @returns vector le where le[i] = max index such that: le[i] < i and
 *          cmp(a[le[i]], a[i]). If no index exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (le[i] = i - 1; le[i] >= 0 && !cmp(a[le[i]], a[i]);) le[i] = le[le[i]];
  return le;
}
/**
 * @code{.cpp}
       vector<int64_t> a;
       RMQ rmq(a, ranges::min); // -std=c++20
       RMQ rmq(a, [&](auto& x, auto& y) { return min(x, y); });
 * @endcode
 */
template <class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  RMQ() {}
  /**
   * @param a static array
   * @param a_op any associative, communative, idempotent operation
   * @time O(n log n)
   * @space O(n log n) for `dp` vector
   */
  RMQ(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= ssize(a); i++) {
      dp.emplace_back(ssize(a) - (2 << i) + 1);
      transform(begin(dp[i]), end(dp[i]) - (1 << i), begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns a[le] op a[le + 1] op ... op a[ri - 1]
   * @time O(1)
   * @space O(1)
   */
  inline T query(int le, int ri) {
    assert(0 <= le && le < ri && ri <= ssize(dp[0]));
    int lg = __lg(ri - le);
    return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
  }
};
/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/LCA.h
 */
struct LCA {
  int n;
  vector<int> in, sub_sz, d, p, order;
  RMQ<int, function<int(int, int)>> rmq;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n log n)
   * @space O(n log n) for rmq, all other vectors are O(n)
   */
  LCA(const vector<vector<int>>& adj) : n(ssize(adj)), in(n), sub_sz(n, 1), d(n), p(n, -1) {
    auto dfs = [&](auto&& self, int u) -> void {
      in[u] = ssize(order), order.push_back(u);
      for (int v : adj[u])
        if (v != p[u])
          d[v] = d[p[v] = u] + 1, self(self, v), sub_sz[u] += sub_sz[v];
    };
    order.reserve(n);
    for (int i = 0; i < n; i++)
      if (p[i] == -1) dfs(dfs, i);
    rmq = {order, [&](int u, int v) { return d[u] < d[v] ? u : v; }};
  }
  /**
   * @param u,v 2 nodes in the same component
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  inline int lca(int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(in[u], in[v]);
    return p[rmq.query(x + 1, y + 1)];
  }
  /**
   * @param u,v endpoint nodes of path
   * @returns number of edges on path
   * @time same as lca(u, v)
   * @space O(1)
   */
  inline int dist_edges(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
  }
  /**
   * @param u,v 2 nodes
   * @returns 1 iff v is in u's subtree
   * @time O(1)
   * @space O(1)
   */
  inline bool in_subtree(int u, int v) {
    return in[u] <= in[v] && in[v] < in[u] + sub_sz[u];
  }
  /**
   * @see https://codeforces.com/blog/entry/71567?#comment-559285
   * @code{.cpp}
         LCA lc(adj);
         int u, v; //to loop over all nodes (except v) on path from u to v:
         for (int i = u; i != v; i = lc.next_on_path(i, v)) {}
   * @endcode
   * @param u,v endpoint nodes of path
   * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[1]
   * @time O(1)
   * @space O(1)
   */
  inline int next_on_path(int u, int v) {
    assert(u != v);
    return in_subtree(u, v) ? rmq.query(in[u] + 1, in[v] + 1) : p[u];
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
   * @time O(k log k); k = ssize(subset)
   * @space O(k) vectors are allocated and returned
   */
  array<vector<int>, 2> compress_tree(vector<int> subset) {
    auto cmp = [&](int u, int v) { return in[u] < in[v]; };
    sort(begin(subset), end(subset), cmp);
    for (int i = 1, siz = ssize(subset); i < siz; i++)
      subset.push_back(lca(subset[i - 1], subset[i]));
    sort(begin(subset), end(subset), cmp);
    subset.erase(unique(begin(subset), end(subset)), end(subset));
    return {mono_st(subset, [&](int u, int v) { return in_subtree(u, v); }), subset};
  }
};
/**
 * @see https://codeforces.com/blog/entry/44351
 * @code{.cpp}
       LCA lc(adj); //required
 * @endcode
 * @param u some node
 * @time O(size of u's subtree)
 * @space O(1)
 */
for (int t = lc.in[u]; t < lc.in[u] + lc.sub_sz[u]; t++) {
  int v = lc.order[t];
