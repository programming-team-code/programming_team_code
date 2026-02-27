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
  int64_t query(int r) {
    int64_t ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  int64_t query(int l, int r) {
    return query(r) - query(l);
  }
  //! Requires sum of [i,i] >= 0
  //! Returns min r s.t. sum of [0,r] >= sum
  //! Returns n if sum of [0,n-1] < sum
  int walk(int64_t sum) {
    if (sum <= 0) return -1;
    int r = 0;
    for (int i = bit_floor(size(s)); i; i /= 2)
      if (r + i <= ssize(s) && s[r + i - 1] < sum)
        sum -= s[(r += i) - 1];
    return r;
  }
};
struct bit_rupq {
  int n;
  BIT bit = {0};
  bit_rupq(int n): n(n), bit(n) {}
  bit_rupq(vector<int64_t> a): n(ssize(a)) {
    adjacent_difference(begin(a), end(a), begin(a));
    bit = {a};
  }
  //! does a[l]+=d, a[l+1]+=d, .., a[r-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int l, int r, int64_t d) {
    if (l < n) bit.update(l, d);
    if (r < n) bit.update(r, -d);
  }
  //! @returns a[i]
  //! @time O(log n)
  //! @space O(1)
  int64_t get_index(int i) { return bit.query(i + 1); }
};
//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://codeforces.com/blog/entry/142176
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   vector<basic_string<int>> adj(n);
//!   edge_cd(adj, [&](const auto& adj, int cent, int m) {
//!     // subtrees of [0, m) of adj[cent]: 1st edge-set
//!     // subtrees of [m, sz(adj[cent])): 2nd edge-set
//!   });
//! @endcode
//! handle single-edge-paths separately
//! @time O(n logφ n)
//! @space O(n)
template<class F, class G> struct edge_cd {
  vector<G> adj;
  F f;
  vector<int> siz;
  edge_cd(const vector<G>& adj, F f):
    adj(adj), f(f), siz(ssize(adj)) {
    dfs(0, ssize(adj) - 1);
  }
  int find_cent(int v, int p, int m) {
    siz[v] = 1;
    for (int u : adj[v])
      if (u != p) {
        int cent = find_cent(u, v, m);
        if (cent != -1) return cent;
        siz[v] += siz[u];
      }
    return 2 * siz[v] > m
           ? p >= 0 && (siz[p] = m + 1 - siz[v]),
           v : -1;
  }
  void dfs(int v, int m) {
    if (m < 2) return;
    v = find_cent(v, -1, m);
    int sum = 0;
    auto it =
      partition(begin(adj[v]), end(adj[v]), [&](int u) {
        int64_t x = sum + siz[u];
        return x * x < m * (m - x) ? sum += siz[u], 1 : 0;
      });
    f(adj, v, it - begin(adj[v]));
    G oth(it, end(adj[v]));
    adj[v].erase(it, end(adj[v]));
    dfs(v, sum);
    swap(adj[v], oth);
    dfs(v, m - sum);
  }
};
//! helper for edge CD: given tree, update node's number,
//! find sum of neighbors' numbers
struct sum_adj {
  int n;
  vector<int64_t> sum, sum_ch;
  vector<int> p;
  //! @param adj undirected, unrooted tree
  //! @param sum sum[u] = initial number for node u
  //! @time O(n)
  //! @space various O(n) vectors are allocated; recursion
  //! stack for dfs is O(n)
  sum_adj(const vector<vector<int>>& adj,
    const vector<int64_t>& sum):
    n(ssize(sum)), sum(sum), sum_ch(n), p(n, -1) {
    auto dfs = [&](auto&& self, int u) -> void {
      for (int c : adj[u])
        if (c != p[u])
          p[c] = u, sum_ch[u] += sum[c], self(self, c);
    };
    dfs(dfs, 0);
  }
  //! @param u node
  //! @param delta number to add
  //! @time O(1)
  //! @space O(1)
  void update(int u, int64_t delta) {
    sum[u] += delta;
    if (p[u] != -1) sum_ch[p[u]] += delta;
  }
  //! @param u node
  //! @returns sum of u's neighbors numbers
  //! @time O(1)
  //! @space O(1)
  int64_t query(int u) {
    return sum_ch[u] + (p[u] != -1 ? sum[p[u]] : 0);
  }
};
//! https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
struct contour_range_update {
  int n;
  vector<int64_t> a;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<bit_rupq, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[u] = initial number for node u
  //! @time O(n logφ n)
  //! @space O(n logφ n) for `info` and `bits`
  contour_range_update(const vector<vector<int>>& adj,
    const vector<int64_t>& a):
    n(ssize(a)), a(a), sum_a(adj, vector<int64_t>(n)),
    info(n) {
    edge_cd(adj,
      [&](const vector<vector<int>>& cd_adj, int cent,
        int split) {
        array<int, 2> mx_d = {0, 0};
        auto dfs = [&](auto&& self, int u, int p, int d,
                     int side) -> void {
          mx_d[side] = max(mx_d[side], d);
          info[u].push_back({int(ssize(bits)), d, side});
          for (int v : cd_adj[u])
            if (v != p) self(self, v, u, 1 + d, side);
        };
        for (int i = 0; i < ssize(cd_adj[cent]); i++)
          dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
        bits.push_back(
          {bit_rupq(mx_d[0] + 1), bit_rupq(mx_d[1] + 1)});
      });
  }
  //! @param u,l,r,delta add delta to all nodes v such
  //! that l <= dist(u, v) < r
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  void update(int u, int l, int r, int64_t delta) {
    if (l <= 0 && 0 < r) a[u] += delta;
    if (l <= 1 && 1 < r) sum_a.update(u, delta);
    for (auto [decomp_id, d, side] : info[u]) {
      auto& bit = bits[decomp_id][!side];
      int my_l = clamp<int>(l - d, 1, bit.n);
      int my_r = clamp<int>(r - d, 1, bit.n);
      bit.update(my_l, my_r, delta);
    }
  }
  //! @param u node
  //! @returns number of node u
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  int64_t query(int u) {
    int64_t sum = a[u] + sum_a.query(u);
    for (auto [decomp_id, d, side] : info[u])
      sum += bits[decomp_id][side].get_index(d);
    return sum;
  }
};
