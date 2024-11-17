#define PROBLEM \
  "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../template.hpp"
#include "../../../library/graphs/bridges_cuts/bridge_tree.hpp"
#include "../../../library/data_structures/dsu/dsu_restorable.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> adj(n);
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    edges[i] = {u, v};
  }
  bridges br(adj, m);
  vector<vector<int>> bt = bridge_tree(adj, br);
  assert(find(begin(br.br_id), end(br.br_id), -1) ==
    end(br.br_id));
  // check correctness of bridge tree
  {
    assert(sz(bt) == br.num_ccs);
    for (int v = 0; v < br.num_ccs; v++)
      for (auto to : bt[v])
        assert(to != v); // didn't add any non-bridge
    int sum_deg = accumulate(begin(bt), end(bt), 0,
      [](int sum, const auto& neighbors) -> int {
        return sum + sz(neighbors);
      });
    int cnt_bridges = accumulate(begin(br.is_bridge),
      end(br.is_bridge), 0);
    assert(sum_deg % 2 == 0 && sum_deg / 2 == cnt_bridges);
  }
  dsu_restorable dsu(n);
  int num_sets_dsu = n;
  for (int i = 0; i < m; i++) {
    if (!br.is_bridge[i]) {
      auto [u, v] = edges[i];
      num_sets_dsu -= dsu.join(u, v);
    }
  }
  assert(num_sets_dsu == sz(bt));
  for (int i = 0; i < m; i++) {
    if (br.is_bridge[i]) {
      auto [u, v] = edges[i];
      bool same_set = dsu.same_set(u, v);
      assert(!same_set);
    }
  }
  for (int i = 0; i < n; i++) {
    int par_of_cc = dsu.find(i);
    assert(br.br_id[i] == br.br_id[par_of_cc]);
  }
  for (int i = 0; i < m; i++) {
    auto [u, v] = edges[i];
    // bridge if nodes are from different 2-edge CCs
    assert(
      br.is_bridge[i] == (br.br_id[u] != br.br_id[v]));
  }
  vector<vector<int>> ccs(br.num_ccs);
  for (int i = 0; i < n; i++)
    ccs[br.br_id[i]].push_back(i);
  cout << br.num_ccs << '\n';
  for (const auto& curr_cc : ccs) {
    cout << sz(curr_cc) << " ";
    for (auto node : curr_cc) cout << node << " ";
    cout << '\n';
  }
  return 0;
}
