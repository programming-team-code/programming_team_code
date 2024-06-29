/**
 * Binary Indexed Tree
 */
template <class T> struct BIT {
  vector<T> s;
  /**
   * @param n initial size
   * @time O(n)
   * @space O(n) for `s` vector
   */
  BIT(int n) : s(n) {}
  BIT() {} /**< allows late initialization */
  /**
   * @param a initial array
   * @time O(n)
   * @space O(n) for `s` vector
   */
  BIT(const vector<T>& a) : s(a) {
    for (int i = 0; i < ((int)size(a)); i++) {
      int j = i | (i + 1);
      if (j < (int)size(a)) s[j] += s[i];
    }
  }
  /**
   * @param i index
   * @param d delta
   * @time O(log n)
   * @space O(1)
   */
  inline void update(int i, T d) {
    assert(0 <= i && i < (int)size(s));
    for (; i < (int)size(s); i |= i + 1) s[i] += d;
  }
  /**
   * @param ri defines range [0, ri)
   * @returns a[0] + a[1] + ... + a[ri - 1]
   * @time O(log n)
   * @space O(1)
   */
  inline T query(int ri) {
    assert(0 <= ri && ri <= (int)size(s));
    T ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns a[le] + a[le + 1] + ... + a[ri - 1]
   * @time O(log n)
   * @space O(1)
   */
  inline T query(int le, int ri) {
    assert(le <= ri);
    return query(ri) - query(le);
  }
  /**
   * Requires bit.sum(i, i + 1) >= 0
   * @param sum see return
   * @returns min pos such that sum of range [0, pos) >= sum (or n+1)
   * @time O(log n)
   * @space O(1)
   */
  inline int lower_bound(T sum) {
    if (sum <= 0) return 0;
    int pos = 0;
    for (int pw = 1 << __lg((int)size(s) | 1); pw; pw >>= 1)
      if (pos + pw <= (int)size(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos + 1;
  }
};
/**
 * helper for edge CD: given tree, update node's number, find sum of neighbors' numbers
 */
template <class T> struct sum_adj {
  int n;
  vector<T> sum, sum_ch;
  vector<int> p;
  /**
   * @param adj undirected, unrooted tree
   * @param a_sum a_sum[u] = initial number for node u
   * @time O(n)
   * @space various O(n) vectors are allocated; recursion stack for dfs is O(n)
   */
  sum_adj(const vector<vector<int>>& adj, const vector<T>& a_sum) : n((int)size(a_sum)), sum(a_sum), sum_ch(n), p(n, -1) {
    auto dfs = [&](auto&& self, int u) -> void {
      for (int v : adj[u])
        if (v != p[u])
          p[v] = u, sum_ch[u] += sum[v], self(self, v);
    };
    dfs(dfs, 0);
  }
  /**
   * @param u node
   * @param delta number to add
   * @time O(1)
   * @space O(1)
   */
  void update(int u, T delta) {
    sum[u] += delta;
    if (p[u] != -1) sum_ch[p[u]] += delta;
  }
  /**
   * @param u node
   * @returns sum of u's neighbors numbers
   * @time O(1)
   * @space O(1)
   */
  T query(int u) { return sum_ch[u] + (p[u] != -1 ? sum[p[u]] : 0); }
};
/**
 * @see https://codeforces.com/blog/entry/104997 https://codeforces.com/blog/entry/120446
 *
 * only handle paths with >=1 edge in each edge-set
 *     (it is guaranteed the edge-sets are non-empty i.e. 0 < split < sz(adj[cent]))
 * don't handle cent<->u paths as these will be handled in some smaller decomposition
 *     (except for single-edge paths, so handle these separately)
 *
 * @code{.cpp}
       edge_cd(adj, [&](const vector<vi>& adj, int cent, int split) {
           // subtrees of prefix [0, split) of adj[cent] are the first edge-set
           // subtrees of suffix [split, sz(adj[cent])) of adj[cent] are the second edge-set
       });
 * @endcode
 */
template <class F> struct edge_cd {
  vector<vector<int>> adj;
  F f;
  vector<int> sub_sz;
  /**
   * @param a_adj,a_f unrooted tree and callback
   * @time O(n * log1.5(n))
   * @space `adj` and `sub_sz` arrays take O(n); recursion stack for `dfs` is
   * O(log1.5 n); recursion stack for `find_cent` is O(n)
   */
  edge_cd(const vector<vector<int>>& a_adj, F a_f) : adj(a_adj), f(a_f), sub_sz((int)size(adj)) {
    dfs(0, (int)size(adj));
  }
  int find_cent(int u, int p, int siz) {
    sub_sz[u] = 1;
    for (int v : adj[u])
      if (v != p) {
        int cent = find_cent(v, u, siz);
        if (cent != -1) return cent;
        sub_sz[u] += sub_sz[v];
      }
    if (p == -1) return u;
    return 2 * sub_sz[u] >= siz ? sub_sz[p] = siz - sub_sz[u], u : -1;
  }
  void dfs(int u, int siz) {
    if (siz <= 2) return;
    u = find_cent(u, -1, siz);
    int sum = 0;
    auto it = partition(begin(adj[u]), end(adj[u]), [&](int v) {
      bool ret = 2 * sum + sub_sz[v] < siz - 1 && 3 * (sum + sub_sz[v]) <= 2 * (siz - 1);
      if (ret) sum += sub_sz[v];
      return ret;
    });
    f(adj, u, it - begin(adj[u]));
    vector<int> oth(it, end(adj[u]));
    adj[u].erase(it, end(adj[u]));
    dfs(u, sum + 1);
    swap(adj[u], oth);
    dfs(u, siz - sum);
  }
};
/**
 * @see https://judge.yosupo.jp/problem /vertex_add_range_contour_sum_on_tree
 */
template <class T> struct contour_range_query {
  int n;
  sum_adj<T> sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<BIT<T>, 2>> bits;
  /**
   * @param adj unrooted, undirected tree
   * @param a a[u] = initial number for node u
   * @time O(n log1.5 n)
   * @space O(n log1.5 n) for `info` and `bits`
   */
  contour_range_query(const vector<vector<int>>& adj, const vector<T>& a) : n((int)size(a)), sum_a(adj, a), info(n) {
    edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) {
      vector<vector<T>> sum_num(2, vector<T>(1));
      auto dfs = [&](auto&& self, int u, int p, int d, int side) -> void {
        info[u].push_back({(int)size(bits), d, side});
        if ((int)size(sum_num[side]) == d) sum_num[side].push_back(0);
        sum_num[side][d] += a[u];
        for (int v : cd_adj[u])
          if (v != p) self(self, v, u, 1 + d, side);
      };
      for (int i = 0; i < ((int)size(cd_adj[cent])); i++)
        dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
      bits.push_back({BIT<T>(sum_num[0]), BIT<T>(sum_num[1])});
    });
  }
  /**
   * @param u node
   * @param delta number to add to node u's number
   * @time O(log1.5(n) * log2(n))
   * @space O(1)
   */
  void update(int u, T delta) {
    sum_a.update(u, delta);
    for (auto [decomp, d, side] : info[u])
      bits[decomp][side].update(d, delta);
  }
  /**
   * @param u node
   * @param le,ri defines range [le, ri)
   * @returns sum of node v's number over all v such that le <= dist_edges(u, v) < ri
   * @time O(log1.5(n) * log2(n))
   * @space O(1)
   */
  T query(int u, int le, int ri) {
    assert(0 <= le && le <= ri && ri <= n);
    T sum = 0;
    if (le <= 0 && 0 < ri) sum += sum_a.sum[u];
    if (le <= 1 && 1 < ri) sum += sum_a.query(u);
    for (auto [decomp, d, side] : info[u]) {
      auto& bit = bits[decomp][!side];
      int my_l = clamp<int>(le - d, 1, (int)size(bit.s));
      int my_r = clamp<int>(ri - d, 1, (int)size(bit.s));
      sum += bit.query(my_l, my_r);
    }
    return sum;
  }
};
