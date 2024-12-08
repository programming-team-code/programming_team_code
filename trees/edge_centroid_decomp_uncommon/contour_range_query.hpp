//! @time O(n + q log n)
//! @space O(n)
struct BIT {
  vector<int64_t> s;
  BIT(int n): s(n) {}
  BIT(const vector<int64_t>& a): s(a) {
    for (int i = 0; i < ssize(a); i++) {
      int j = i | (i + 1);
      if (j < ssize(a)) s[j] += s[i];
    }
  }
  void update(int i, int64_t d) {
    for (; i < ssize(s); i |= i + 1) s[i] += d;
  }
  int64_t query(int r) { // [0, r)
    int64_t ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  int64_t query(int l, int r) { // [l, r)
    return query(r) - query(l);
  }
  //! Requires s[i] >= 0
  //! max pos such that sum of [0,pos) < sum, or -1
  int walk(int64_t sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = bit_floor(size(s)); pw; pw >>= 1)
      if (pos + pw <= ssize(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos;
  }
};
//! helper for edge CD: given tree, update node's number,
//! find sum of neighbors' numbers
struct sum_adj {
  int n;
  vector<int64_t> sum, sum_ch;
  vector<int> p;
  //! @param adj undirected, unrooted tree
  //! @param sum sum[v] = initial number for node v
  //! @time O(n)
  //! @space various O(n) vectors are allocated; recursion
  //! stack for dfs is O(n)
  sum_adj(const vector<vector<int>>& adj,
    const vector<int64_t>& sum):
    n(ssize(sum)), sum(sum), sum_ch(n), p(n, -1) {
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
  void update(int v, int64_t delta) {
    sum[v] += delta;
    if (p[v] != -1) sum_ch[p[v]] += delta;
  }
  //! @param v node
  //! @returns sum of v's neighbors numbers
  //! @time O(1)
  //! @space O(1)
  int64_t query(int v) {
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
  edge_cd(const vector<vector<int>>& adj, F f):
    adj(adj), f(f), sub_sz(ssize(adj)) {
    dfs(0, ssize(adj));
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
//! https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree
struct contour_range_query {
  int n;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<BIT, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[v] = initial number for node v
  //! @time O(n log1.5 n)
  //! @space O(n log1.5 n) for `info` and `bits`
  contour_range_query(const vector<vector<int>>& adj,
    const vector<int64_t>& a):
    n(ssize(a)), sum_a(adj, a), info(n) {
    edge_cd(adj,
      [&](const vector<vector<int>>& cd_adj, int cent,
        int split) {
        vector<vector<int64_t>> sum_num(2,
          vector<int64_t>(1));
        auto dfs = [&](auto&& self, int v, int p, int d,
                     int side) -> void {
          info[v].push_back({int(ssize(bits)), d, side});
          if (ssize(sum_num[side]) == d)
            sum_num[side].push_back(0);
          sum_num[side][d] += a[v];
          for (int u : cd_adj[v])
            if (u != p) self(self, u, v, 1 + d, side);
        };
        for (int i = 0; i < ssize(cd_adj[cent]); i++)
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
        bits.push_back({BIT(sum_num[0]), BIT(sum_num[1])});
      });
  }
  //! @param v node
  //! @param delta number to add to node v's number
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  void update(int v, int64_t delta) {
    sum_a.update(v, delta);
    for (auto [decomp, d, side] : info[v])
      bits[decomp][side].update(d, delta);
  }
  //! @param v node
  //! @param l,r defines range [l, r)
  //! @returns sum of node u's number over all u such that
  //! l
  //! <= dist_edges(u, v) < r
  //! @time O(log1.5(n) * log2(n))
  //! @space O(1)
  int64_t query(int v, int l, int r) {
    int64_t sum = 0;
    if (l <= 0 && 0 < r) sum += sum_a.sum[v];
    if (l <= 1 && 1 < r) sum += sum_a.query(v);
    for (auto [decomp, d, side] : info[v]) {
      auto& bit = bits[decomp][!side];
      int my_l = clamp<int>(l - d, 1, ssize(bit.s));
      int my_r = clamp<int>(r - d, 1, ssize(bit.s));
      sum += bit.query(my_l, my_r);
    }
    return sum;
  }
};
