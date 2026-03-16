#define PROBLEM \
  "https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/bit_uncommon/rupq.hpp"
#include "../../../library/trees/edge_cd.hpp"
struct sum_adj {
  int n;
  vector<ll> sum, sum_ch;
  vi p;
  //! @param adj undirected, unrooted tree
  //! @param sum sum[u] = initial number for node u
  //! @time O(n)
  //! @space various O(n) vectors are allocated; recursion
  //! stack for dfs is O(n)
  sum_adj(const vector<vi>& adj, const vector<ll>& sum):
    n(sz(sum)), sum(sum), sum_ch(n), p(n, -1) {
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
  void update(int u, ll delta) {
    sum[u] += delta;
    if (p[u] != -1) sum_ch[p[u]] += delta;
  }
  //! @param u node
  //! @returns sum of u's neighbors numbers
  //! @time O(1)
  //! @space O(1)
  ll query(int u) {
    return sum_ch[u] + (p[u] != -1 ? sum[p[u]] : 0);
  }
};
//! https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
struct contour_range_update {
  int n;
  vector<ll> a;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<bit_rupq, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[u] = initial number for node u
  //! @time O(n logφ n)
  //! @space O(n logφ n) for `info` and `bits`
  contour_range_update(vector<vi> adj,
    const vector<ll>& a):
    n(sz(a)), a(a), sum_a(adj, vector<ll>(n)), info(n) {
    edge_cd(adj, [&](int cent, int split) {
      array<int, 2> mx_d = {0, 0};
      auto dfs = [&](auto&& self, int u, int p, int d,
                   int side) -> void {
        mx_d[side] = max(mx_d[side], d);
        info[u].push_back({int(sz(bits)), d, side});
        for (int v : adj[u])
          if (v != p) self(self, v, u, 1 + d, side);
      };
      rep(i, 0, sz(adj[cent]))
        dfs(dfs, adj[cent][i], cent, 1, i < split);
      bits.push_back(
        {bit_rupq(mx_d[0] + 1), bit_rupq(mx_d[1] + 1)});
    });
  }
  //! @param u,l,r,delta add delta to all nodes v such
  //! that l <= dist(u, v) < r
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  void update(int u, int l, int r, ll delta) {
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
  ll query(int u) {
    ll sum = a[u] + sum_a.query(u);
    for (auto [decomp_id, d, side] : info[u])
      sum += bits[decomp_id][side].get_index(d);
    return sum;
  }
};
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  contour_range_update cu(adj, a);
  {
#include "../edge_cd_asserts.hpp"
    edge_cd(adj, edge_cd_asserts);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int u, l, r, delta;
      cin >> u >> l >> r >> delta;
      cu.update(u, l, l, delta);
      cu.update(u, l, r, delta);
      cu.update(u, r, r, delta);
    } else {
      assert(type == 1);
      int u;
      cin >> u;
      cout << cu.query(u) << '\n';
    }
  }
  return 0;
}
