#define PROBLEM \
  "https://judge.yosupo.jp/problem/incremental_scc"
#include "../template.hpp"
#include "../../../library/graphs/strongly_connected_components/offline_incremental_scc.hpp"
#include "../../../library/data_structures/dsu/dsu.hpp"
const int mod = 998244353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<int> xs(n);
  for (int i = 0; i < n; i++) cin >> xs[i];
  vector<array<int, 2>> eds(m);
  for (auto& [u, v] : eds) cin >> u >> v;
  auto joins = offline_incremental_scc(eds, n);
  // assert joins[i] == -1 for self-edges
  for (int t = 0; t < m; t++)
    assert((eds[t][0] == eds[t][1]) == (joins[t] == -1));
  vector<int> order(m);
  iota(all(order), 0);
  ranges::sort(all(order), {},
    [&](int i) { return joins[i]; });
  DSU dsu(n);
  int sum = 0;
  for (int t = 0, it = 0; t < m; t++) {
    while (it < m && joins[order[it]] <= t) {
      auto [u, v] = eds[order[it]];
      u = dsu.f(u);
      v = dsu.f(v);
      if (dsu.p[u] > dsu.p[v]) swap(u, v);
      if (u != v) {
        sum = (sum + 1LL * xs[u] * xs[v]) % mod;
        xs[u] = (xs[u] + xs[v]) % mod;
        xs[v] = xs[u];
      }
      dsu.join(u, v);
      it++;
    }
    cout << sum << '\n';
  }
  return 0;
}
