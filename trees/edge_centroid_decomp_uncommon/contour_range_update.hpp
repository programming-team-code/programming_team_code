//! @code
//!   BIT<int> bit1(n);
//!   BIT<ll> bit2(n);
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T> struct BIT {
  vector<T> s;
  BIT(int n): s(n) {}
  BIT(const vector<T>& a): s(a) {
    for (int i = 0; i < ((int)size(a)); i++) {
      int j = i | (i + 1);
      if (j < (int)size(a)) s[j] += s[i];
    }
  }
  void update(int i, T d) {
    for (; i < (int)size(s); i |= i + 1) s[i] += d;
  }
  T query(int ri) { // [0, ri)
    T ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  T query(int le, int ri) { // [le, ri)
    return query(ri) - query(le);
  }
  //! Requires bit.query(i,i+1) >= 0
  //! @returns max pos such that sum of [0,pos) < sum
  int lower_bound(T sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << __lg((int)size(s) | 1); pw;
         pw >>= 1)
      if (
        pos + pw <= (int)size(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos;
  }
};
template<class T> struct bit_rupq {
  int n;
  BIT<T> bit = {0};
  bit_rupq(int a_n): n(a_n), bit(n) {}
  bit_rupq(vector<T> a): n((int)size(a)) {
    adjacent_difference(begin(a), end(a), begin(a));
    bit = {a};
  }
  //! does a[le]+=d, a[le+1]+=d, .., a[ri-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int le, int ri, T d) {
    if (le < n) bit.update(le, d);
    if (ri < n) bit.update(ri, -d);
  }
  //! @returns a[i]
  //! @time O(log n)
  //! @space O(1)
  T get_index(int i) { return bit.query(i + 1); }
};
//! helper for edge CD: given tree, update node's number,
//! find sum of neighbors' numbers
template<class T> struct sum_adj {
  int n;
  vector<T> sum, sum_ch;
  vector<int> p;
  //! @param adj undirected, unrooted tree
  //! @param a_sum a_sum[v] = initial number for node v
  //! @time O(n)
  //! @space various O(n) vectors are allocated; recursion
  //! stack for dfs is O(n)
  sum_adj(const vector<vector<int>>& adj,
    const vector<T>& a_sum):
    n((int)size(a_sum)), sum(a_sum), sum_ch(n), p(n, -1) {
    auto dfs = [&](auto&& self, int v) -> void {
      for (int u : adj[v])
        if (u != p[v])
          p[u] = v, sum_ch[v] += sum[u], self(self, u);
    };
    dfs(dfs, 0);
  }
  //! @param v node
  //! @param delta number to add
  //! @time O(1)
  //! @space O(1)
  void update(int v, T delta) {
    sum[v] += delta;
    if (p[v] != -1) sum_ch[p[v]] += delta;
  }
  //! @param v node
  //! @returns sum of v's neighbors numbers
  //! @time O(1)
  //! @space O(1)
  T query(int v) {
    return sum_ch[v] + (p[v] != -1 ? sum[p[v]] : 0);
  }
};
//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   edge_cd(adj, [&](const vector<vi>& adj,
//!     int cent, int split) {
//!     // subtrees of prefix [0, split) of adj[cent]
//!     //   are the first edge-set
//!     // subtrees of suffix [split, sz(adj[cent]))
//!     //   of adj[cent] are the second edge-set
//!   });
//! @endcode
//! handle single-edge-paths separately
//! @time O(n log1.5 n)
//! @space O(n)
template<class F> struct edge_cd {
  vector<vector<int>> adj;
  F f;
  vector<int> sub_sz;
  edge_cd(const vector<vector<int>>& a_adj, F a_f):
    adj(a_adj), f(a_f), sub_sz((int)size(adj)) {
    dfs(0, (int)size(adj));
  }
  int find_cent(int v, int p, int siz) {
    sub_sz[v] = 1;
    for (int u : adj[v])
      if (u != p) {
        int cent = find_cent(u, v, siz);
        if (cent != -1) return cent;
        sub_sz[v] += sub_sz[u];
      }
    if (p == -1) return v;
    return 2 * sub_sz[v] >= siz
           ? sub_sz[p] = siz - sub_sz[v],
             v : -1;
  }
  void dfs(int v, int siz) {
    if (siz <= 2) return;
    v = find_cent(v, -1, siz);
    int sum = 0;
    auto it =
      partition(begin(adj[v]), end(adj[v]), [&](int u) {
        bool ret = 2 * sum + sub_sz[u] < siz - 1 &&
          3 * (sum + sub_sz[u]) <= 2 * (siz - 1);
        if (ret) sum += sub_sz[u];
        return ret;
      });
    f(adj, v, it - begin(adj[v]));
    vector<int> oth(it, end(adj[v]));
    adj[v].erase(it, end(adj[v]));
    dfs(v, sum + 1);
    swap(adj[v], oth);
    dfs(v, siz - sum);
  }
};
//! https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
template<class T> struct contour_range_update {
  int n;
  vector<T> a;
  sum_adj<T> sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<bit_rupq<T>, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a_a a_a[v] = initial number for node v
  //! @time O(n log1.5 n)
  //! @space O(n log1.5 n) for `info` and `bits`
  contour_range_update(const vector<vector<int>>& adj,
    const vector<T>& a_a):
    n((int)size(a_a)), a(a_a), sum_a(adj, vector<T>(n)),
    info(n) {
    edge_cd(adj,
      [&](const vector<vector<int>>& cd_adj, int cent,
        int split) {
        array<int, 2> mx_d = {0, 0};
        auto dfs = [&](auto&& self, int v, int p, int d,
                     int side) -> void {
          mx_d[side] = max(mx_d[side], d);
          info[v].push_back({(int)size(bits), d, side});
          for (int u : cd_adj[v])
            if (u != p) self(self, u, v, 1 + d, side);
        };
        for (int i = 0; i < ((int)size(cd_adj[cent])); i++)
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
        bits.push_back({bit_rupq<T>(mx_d[0] + 1),
          bit_rupq<T>(mx_d[1] + 1)});
      });
  }
  //! @param v,le,ri,delta add delta to all nodes u such
  //! that le <= dist_edges(v, u) < ri
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  void update(int v, int le, int ri, T delta) {
    if (le <= 0 && 0 < ri) a[v] += delta;
    if (le <= 1 && 1 < ri) sum_a.update(v, delta);
    for (auto [decomp_id, d, side] : info[v]) {
      auto& bit = bits[decomp_id][!side];
      int my_l = clamp<int>(le - d, 1, bit.n);
      int my_r = clamp<int>(ri - d, 1, bit.n);
      bit.update(my_l, my_r, delta);
    }
  }
  //! @param v node
  //! @returns number of node v
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  T query(int v) {
    T sum = a[v] + sum_a.query(v);
    for (auto [decomp_id, d, side] : info[v])
      sum += bits[decomp_id][side].get_index(d);
    return sum;
  }
};
