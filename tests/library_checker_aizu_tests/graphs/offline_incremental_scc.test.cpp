#define PROBLEM "https://judge.yosupo.jp/problem/incremental_scc"
#include "../../../library/graphs/strongly_connected_components/offline_incremental_scc.hpp"

#include "../../../kactl/content/data-structures/UnionFind.h"
#include "../../../library/math/mod_int.hpp"
#include "../template.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<mint> xs(n);
  for (int i = 0; i < n; i++) cin >> xs[i].x;
  vector<array<int, 2>> eds(m);
  for (auto& [u, v] : eds) cin >> u >> v;
  auto joins = offline_incremental_scc(eds, n);
  // assert joins[i] == -1 for self-edges
  for (int t = 0; t < m; t++)
    assert((eds[t][0] == eds[t][1]) == (joins[t] == -1));
  vector<int> order(m);
  iota(all(order), 0);
  ranges::sort(all(order), {}, [&](int i) { return joins[i]; });
  UF uf(n);
  mint sum = 0;
  for (int t = 0, it = 0; t < m; t++) {
    while (it < m && joins[order[it]] <= t) {
      auto [u, v] = eds[order[it]];
      u = uf.find(u);
      v = uf.find(v);
      if (uf.e[u] > uf.e[v]) swap(u, v);
      if (u != v) {
        sum = sum + xs[u] * xs[v];
        xs[u] = xs[u] + xs[v];
        xs[v] = xs[u];
      }
      uf.join(u, v);
      it++;
    }
    cout << sum.x << '\n';
  }
  return 0;
}
