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
int lsb(int x) { return x & -x; }
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
struct linear_lca {
  struct node {
    int d, sub_sz = 1, in, label, asc;
  };
  vector<node> t;
  vector<int> head;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_lca(const vector<vector<int>>& adj) : t((int)size(adj)), head((int)size(t) + 1) {
    vector<pair<int, int>> order;
    auto dfs = [&](auto&& self, int v, int p) -> void {
      order.emplace_back(v, p);
      t[v].in = t[v].label = (int)size(order);
      for (int u : adj[v])
        if (u != p) {
          t[u].d = 1 + t[v].d;
          self(self, u, v);
          head[t[u].label] = v;
          t[v].sub_sz += t[u].sub_sz;
          if (lsb(t[u].label) > lsb(t[v].label)) t[v].label = t[u].label;
        }
    };
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].d == 0) dfs(dfs, i, i);
    for (auto [v, p] : order) t[v].asc = t[p].asc | lsb(t[v].label);
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  int lca(int u, int v) {
    if (int j = t[u].label ^ t[v].label; j) {
      j = t[u].asc & t[v].asc & -(1 << __lg(j));
      if (int k = t[u].asc ^ j; k) k = 1 << __lg(k), u = head[(t[u].label & -k) | k];
      if (int k = t[v].asc ^ j; k) k = 1 << __lg(k), v = head[(t[v].label & -k) | k];
    }
    return t[u].d < t[v].d ? u : v;
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
