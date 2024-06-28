#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C"

// code is 30,000^2, it was nearly 50x slower in DEBUG mode
#undef _GLIBCXX_DEBUG

#include "../template.hpp"
#include "../../../library/graphs/strongly_connected_components/scc.hpp"
#include "../../../library/graphs/strongly_connected_components/offline_incremental_scc.hpp"
#include "../../../library/contest/random.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<array<int, 2>> eds(m);
  for (auto& [u, v] : eds) cin >> u >> v;
  shuffle(begin(eds), end(eds), rng);
  auto joins = offline_incremental_scc(eds, n);
  vector<vector<int>> adj(n);
  for (int t = 0; t < m; t++) {
    adj[eds[t][0]].push_back(eds[t][1]);
    auto scc_id = sccs(adj).scc_id;
    for (auto it = 0; it < m; it++) {
      auto [u, v] = eds[it];
      if (scc_id[u] == scc_id[v]) {
        assert(joins[it] <= t);
      } else {
        assert(joins[it] > t);
      }
    }
  }
  auto scc_id = sccs(adj).scc_id;
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << (scc_id[u] == scc_id[v]) << '\n';
  }
  return 0;
}
