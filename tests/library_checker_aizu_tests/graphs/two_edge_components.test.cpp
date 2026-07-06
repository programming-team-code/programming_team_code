#define PROBLEM \
  "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../template.hpp"
#include "../../../library/graphs/uncommon/bridge_tree.hpp"
#include "../../../library/dsu/dsu.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pii>> adj(n);
  vector<pii> edges(m);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    edges[i] = {u, v};
  }
  auto [num_ccs, br_id, is_br] = bridges(adj, m);
  auto bt = bridge_tree(adj, num_ccs, br_id, is_br);
  assert(ranges::find(br_id, -1) == end(br_id));
  // check correctness of bridge tree
  {
    assert(sz(bt) == num_ccs);
    rep(v, 0, num_ccs) for (auto to : bt[v])
      assert(to != v); // didn't add any non-bridge
    int sum_deg = accumulate(all(bt), 0,
      [](int sum, const auto& neighbors) -> int {
        return sum + sz(neighbors);
      });
    int cnt_bridges = accumulate(all(is_br), 0);
    assert(sum_deg % 2 == 0 && sum_deg / 2 == cnt_bridges);
  }
  DSU dsu(n);
  int num_sets_dsu = n;
  rep(i, 0, m) {
    if (!is_br[i]) {
      auto [u, v] = edges[i];
      num_sets_dsu -= dsu.join(u, v);
    }
  }
  assert(num_sets_dsu == sz(bt));
  rep(i, 0, m) {
    if (is_br[i]) {
      auto [u, v] = edges[i];
      assert(dsu.f(u) != dsu.f(v));
    }
  }
  rep(i, 0, n) {
    int par_of_cc = dsu.f(i);
    assert(br_id[i] == br_id[par_of_cc]);
  }
  rep(i, 0, m) {
    auto [u, v] = edges[i];
    // bridge if nodes are from different 2-edge CCs
    assert(is_br[i] == (br_id[u] != br_id[v]));
  }
  vector<vi> ccs(num_ccs);
  rep(i, 0, n) ccs[br_id[i]].push_back(i);
  cout << num_ccs << '\n';
  for (const auto& curr_cc : ccs) {
    cout << sz(curr_cc) << " ";
    for (auto node : curr_cc) cout << node << " ";
    cout << '\n';
  }
  return 0;
}
