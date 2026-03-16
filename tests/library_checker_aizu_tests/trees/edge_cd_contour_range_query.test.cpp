#define PROBLEM \
  "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/bit.hpp"
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
struct contour_range_query {
  int n;
  sum_adj sum_a;
  vector<vector<array<int, 3>>> info;
  vector<array<BIT, 2>> bits;
  //! @param adj unrooted, undirected tree
  //! @param a a[u] = initial number for node u
  //! @time O(n logφ n)
  //! @space O(n logφ n) for `info` and `bits`
  contour_range_query(vector<vi> adj, const vector<ll>& a):
    n(sz(a)), sum_a(adj, a), info(n) {
    edge_cd(adj, [&](int cent, int split) {
      vector<vector<ll>> sum_num(2, vector<ll>(1));
      auto dfs = [&](auto&& self, int u, int p, int d,
                   int side) -> void {
        info[u].push_back({int(sz(bits)), d, side});
        if (sz(sum_num[side]) == d)
          sum_num[side].push_back(0);
        sum_num[side][d] += a[u];
        for (int c : adj[u])
          if (c != p) self(self, c, u, 1 + d, side);
      };
      rep(i, 0, sz(adj[cent]))
        dfs(dfs, adj[cent][i], cent, 1, i < split);
      bits.push_back({BIT(sum_num[0]), BIT(sum_num[1])});
    });
  }
  //! @param u node
  //! @param delta number to add to node u's number
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  void update(int u, ll delta) {
    sum_a.update(u, delta);
    for (auto [decomp, d, side] : info[u])
      bits[decomp][side].update(d, delta);
  }
  //! @param u node
  //! @param l,r defines range [l, r)
  //! @returns sum of node v's number over all v such that
  //! l <= dist(u, v) < r
  //! @time O(logφ(n) * log2(n))
  //! @space O(1)
  ll query(int u, int l, int r) {
    ll sum = 0;
    if (l <= 0 && 0 < r) sum += sum_a.sum[u];
    if (l <= 1 && 1 < r) sum += sum_a.query(u);
    for (auto [decomp, d, side] : info[u]) {
      auto& bit = bits[decomp][!side];
      int my_l = clamp<int>(l - d, 1, sz(bit.s));
      int my_r = clamp<int>(r - d, 1, sz(bit.s));
      sum += bit.query(my_l, my_r);
    }
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
  contour_range_query cq(adj, a);
  {
#include "../edge_cd_asserts.hpp"
    edge_cd(adj, edge_cd_asserts);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int u;
      ll delta;
      cin >> u >> delta;
      cq.update(u, delta);
    } else {
      assert(type == 1);
      int u, l, r;
      cin >> u >> l >> r;
      ll res = cq.query(u, l, l);
      assert(res == 0);
      res = cq.query(u, r, r);
      assert(res == 0);
      cout << cq.query(u, l, r) << '\n';
    }
  }
  return 0;
}
