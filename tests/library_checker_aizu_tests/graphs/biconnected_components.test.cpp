#define PROBLEM \
  "https://judge.yosupo.jp/problem/biconnected_components"
#include "../template.hpp"
#include "../../../library/graphs/bridges_cuts/block_vertex_tree.hpp"
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
    edges[i] = make_pair(u, v);
  }
  auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
  vector<vector<int>> bvt =
    block_vertex_tree(adj, num_bccs, bcc_id);
  assert(
    find(begin(bcc_id), end(bcc_id), -1) == end(bcc_id));
  for (int i = 0; i < n; i++) {
    // cut node if there exists a pair of adjacent edges
    // belonging to different BCCs
    bool curr_is_cut = 0;
    for (int j = 0; j < sz(adj[i]); j++)
      if (bcc_id[adj[i][0].second] !=
        bcc_id[adj[i][j].second])
        curr_is_cut = 1;
    assert(curr_is_cut == is_cut[i]);
  }
  // check correctness of block vertex tree
  for (int i = 0; i < n; i++) {
    assert(sz(adj[i]) >=
      sz(bvt[i])); // in particular, if empty(adj[i]), then
                   // empty(bct[i])
    assert(is_cut[i] ==
      (sz(bvt[i]) >
        1)); // is cut means non-leaf in block vertex tree
  }
  {
    vector<set<int>> bcc_to_nodes(num_bccs),
      node_to_bccs(n);
    for (int i = 0; i < m; i++) {
      int bccid = bcc_id[i];
      for (auto node : {edges[i].first, edges[i].second}) {
        bcc_to_nodes[bccid].insert(node);
        node_to_bccs[node].insert(bccid);
      }
    }
    // testing commented loops in block_vertex_tree
    for (int u = 0; u < n; u++) {
      assert(sz(node_to_bccs[u]) == sz(bvt[u]));
      for (auto bccid : bvt[u]) {
        bccid -= n;
        assert(node_to_bccs[u].contains(bccid));
      }
    }
    for (int bccid = 0; bccid < num_bccs; bccid++) {
      assert(
        sz(bcc_to_nodes[bccid]) == sz(bvt[bccid + n]));
      for (auto u : bvt[bccid + n])
        assert(bcc_to_nodes[bccid].contains(u));
    }
  }
  vector<int> lone_nodes;
  for (int u = 0; u < n; u++)
    if (empty(bvt[u])) lone_nodes.push_back(u);
  cout << num_bccs + sz(lone_nodes) << '\n';
  for (int bccid = 0; bccid < num_bccs; bccid++) {
    cout << sz(bvt[bccid + n]) << " ";
    for (auto u : bvt[bccid + n]) cout << u << " ";
    cout << '\n';
  }
  for (auto u : lone_nodes) cout << "1 " << u << '\n';
  return 0;
}
