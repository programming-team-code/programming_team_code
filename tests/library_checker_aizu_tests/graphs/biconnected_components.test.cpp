#define PROBLEM \
  "https://judge.yosupo.jp/problem/biconnected_components"
#include "../template.hpp"
#include "../../../library/graphs/uncommon/block_vertex_tree.hpp"
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
    edges[i] = make_pair(u, v);
  }
  auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
  auto bvt = block_vertex_tree(adj, num_bccs, bcc_id);
  assert(ranges::find(bcc_id, -1) == end(bcc_id));
  rep(i, 0, n) {
    // cut node if there exists a pair of adjacent edges
    // belonging to different BCCs
    bool curr_is_cut = 0;
    rep(j, 0, sz(adj[i])) if (
      bcc_id[adj[i][0].second] != bcc_id[adj[i][j].second])
      curr_is_cut = 1;
    assert(curr_is_cut == is_cut[i]);
  }
  // check correctness of block vertex tree
  rep(i, 0, n) {
    // in particular, if empty(adj[i]), then empty(bct[i])
    assert(sz(adj[i]) >= sz(bvt[i]));
    // is cut means non-leaf in block vertex tree
    assert(is_cut[i] == (sz(bvt[i]) > 1));
  }
  {
    vector<set<int>> bcc_to_nodes(num_bccs),
      node_to_bccs(n);
    rep(i, 0, m) {
      int bccid = bcc_id[i];
      for (auto node : {edges[i].first, edges[i].second}) {
        bcc_to_nodes[bccid].insert(node);
        node_to_bccs[node].insert(bccid);
      }
    }
    // testing commented loops in block_vertex_tree
    rep(u, 0, n) {
      assert(sz(node_to_bccs[u]) == sz(bvt[u]));
      for (auto bccid : bvt[u]) {
        bccid -= n;
        assert(node_to_bccs[u].contains(bccid));
      }
    }
    rep(bccid, 0, num_bccs) {
      assert(
        sz(bcc_to_nodes[bccid]) == sz(bvt[bccid + n]));
      for (auto u : bvt[bccid + n])
        assert(bcc_to_nodes[bccid].contains(u));
    }
  }
  vi lone_nodes;
  rep(u, 0, n) if (empty(bvt[u])) lone_nodes.push_back(u);
  cout << num_bccs + sz(lone_nodes) << '\n';
  rep(bccid, 0, num_bccs) {
    cout << sz(bvt[bccid + n]) << " ";
    for (auto u : bvt[bccid + n]) cout << u << " ";
    cout << '\n';
  }
  for (auto u : lone_nodes) cout << "1 " << u << '\n';
  return 0;
}
