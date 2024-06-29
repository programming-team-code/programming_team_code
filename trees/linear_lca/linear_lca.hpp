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
inline int bit_floor(unsigned x) { return x ? 1 << __lg(x) : 0; }
inline int lsb(int x) { return x & -x; }
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
struct linear_lca {
  int n;
  vector<int> d, p, head, in, order, big_ch;
  vector<unsigned> label, asc;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_lca(const vector<vector<int>>& adj) : n(size(adj)), d(n), p(n), head(n + 1), in(n), big_ch(n), label(n), asc(n) {
    auto dfs = [&](auto&& self, int u) -> void {
      order.push_back(u);
      in[u] = label[u] = (int)size(order);
      for (int v : adj[u])
        if (v != p[u]) {
          d[v] = 1 + d[p[v] = u];
          self(self, v);
          if (lsb(label[v]) > lsb(label[u]))
            label[u] = label[big_ch[u] = v];
        }
      head[label[u]] = u;
    };
    for (int i = 0; i < (n); i++)
      if (in[i] == 0) p[i] = i, dfs(dfs, i);
    for (int u : order) asc[u] = lsb(label[u]) | asc[p[u]];
  }
  inline int lift(int u, unsigned j) {
    auto k = bit_floor(asc[u] ^ j);
    return k == 0 ? u : p[head[(label[u] & -k) | k]];
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  inline int lca(int u, int v) {
    auto [x, y] = minmax(label[u], label[v]);
    auto j = asc[u] & asc[v] & -bit_floor((x - 1) ^ y);
    return d[u = lift(u, j)] < d[v = lift(v, j)] ? u : v;
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
    if ((asc[u] & asc[v]) != asc[u]) return 0;
    v = lift(v, asc[u]);
    return label[u] == label[v] && d[u] <= d[v];
  }
  /**
   * @code{.cpp}
         int u, v; //to loop over all nodes (except v) on path from u to v:
         for (int i = u; i != v; i = lin_lca.next_on_path(i, v)) {}
   * @endcode
   * @param u,v endpoint nodes of path
   * @returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[1]
   * @time O(1)
   * @space O(1)
   */
  inline int next_on_path(int u, int v) {
    assert(u != v);
    if ((asc[u] & asc[v]) != asc[u]) return p[u];
    if (asc[u] != asc[v]) {
      auto k = bit_floor(asc[u] ^ asc[v]);
      v = head[(label[v] & -k) | k];
    }
    if (label[u] != label[p[v]] || d[u] >= d[v]) return p[u];
    return p[v] == u ? v : big_ch[u];
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
    auto cmp = [&](int u, int v) { return in[u] < in[v]; };
    sort(begin(subset), end(subset), cmp);
    int siz = (int)size(subset);
    for (int i = 1; i < (siz); i++)
      subset.push_back(lca(subset[i - 1], subset[i]));
    sort(begin(subset), end(subset), cmp);
    subset.erase(unique(begin(subset), end(subset)), end(subset));
    return {mono_st(subset, [&](int u, int v) { return in_subtree(u, v); }), subset};
  }
};
