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
/**
 * @see Still Simpler Static Level Ancestors by Torben Hagerup, May 2020; https://codeforces.com/blog/entry/126580
 */
struct linear_kth_par {
  struct node {
    int d, p = -1, dl /*deepest leaf*/, idx;
    vector<int> lad;
  };
  vector<node> t;
  vector<int> j;
  /**
   * @code{.cpp}
             linear_kth_par kp(adj);
   * @endcode
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_kth_par(const vector<vector<int>>& adj) : t((int)size(adj)), j(2 * (int)size(t)) {
    vector<int> st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] = st[max(0, (int)size(st) - 1 - 2 * (pos & -pos))];
      pos++;
    };
    auto dfs = [&](auto&& self, int v) -> void {
      st.push_back(v);
      t[v].idx = pos;
      t[v].dl = v;
      add_j();
      for (int u : adj[v])
        if (u != t[v].p) {
          t[u].d = t[t[u].p = v].d + 1;
          self(self, u);
          if (t[t[u].dl].d > t[t[v].dl].d) t[v].dl = t[u].dl;
          add_j();
        }
      st.pop_back();
    };
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].p == -1) t[i].p = i, dfs(dfs, i);
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].p == i || t[t[i].p].dl != t[i].dl) {
        int leaf = t[i].dl;
        vector<int>& lad = t[leaf].lad;
        lad.resize(min((t[leaf].d - t[i].d) * 7 / 2, t[leaf].d + 1), leaf);
        for (int k = 1; k < ((int)size(lad)); k++)
          lad[k] = t[lad[k - 1]].p;
      }
  }
  /**
   * @param v query node
   * @param k number of edges
   * @returns a node k edges up from v
   * @time O(1)
   * @space O(1)
   */
  int kth_par(int v, int k) {
    switch (k) {
      case 0: return v;
      case 1: return t[v].p;
      case 2: return t[t[v].p].p;
      default:
        int i = 1 << __lg(k / 3), leaf = t[j[(t[v].idx & -i) | i]].dl;
        return t[leaf].lad[k + t[leaf].d - t[v].d];
    }
  }
};
struct linear_kth_path {
  linear_lca lin_lca;
  linear_kth_par lin_kp;
  linear_kth_path(const vector<vector<int>>& adj) : lin_lca(adj), lin_kp(adj) {}
  /**
   * @param u,v endpoint nodes of path
   * @param k index into path
   * @returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[k], or -1, so u if k=0
   * @time O(1)
   * @space O(1)
   */
  int kth_path(int u, int v, int k) {
    int lca_d = lin_kp.t[lin_lca.lca(u, v)].d;
    int u_lca = lin_kp.t[u].d - lca_d;
    int v_lca = lin_kp.t[v].d - lca_d;
    if (k <= u_lca) return lin_kp.kth_par(u, k);
    if (k <= u_lca + v_lca) return lin_kp.kth_par(v, u_lca + v_lca - k);
    return -1;
  }
};
