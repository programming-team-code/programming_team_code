#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../template.hpp"

#include "../../../library/graphs/bridges_cuts/block_vertex_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<array<int, 2>>> adj(n);
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
    edges[i] = make_pair(u, v);
  }
  cuts cc(adj, m);
  vector<vector<int>> bvt = block_vertex_tree(adj, cc);
  assert(find(begin(cc.bcc_id), end(cc.bcc_id), -1) == end(cc.bcc_id));
  for (int i = 0; i < n; i++) {
    // cut node if there exists a pair of adjacent edges belonging to different BCCs
    bool is_cut = 0;
    for (int j = 0; j < ssize(adj[i]); j++) {
      if (cc.bcc_id[adj[i][0][1]] != cc.bcc_id[adj[i][j][1]])
        is_cut = 1;
    }
    assert(is_cut == cc.is_cut[i]);
  }
  // check correctness of block vertex tree
  for (int i = 0; i < n; i++) {
    assert(ssize(adj[i]) >= ssize(bvt[i]));  // in particular, if empty(adj[i]), then empty(bct[i])
    assert(cc.is_cut[i] == (ssize(bvt[i]) > 1));  // is cut means non-leaf in block vertex tree
  }
  {
    vector<set<int>> bcc_to_nodes(cc.num_bccs), node_to_bccs(n);
    for (int i = 0; i < m; i++) {
      int bccid = cc.bcc_id[i];
      for (auto node : {edges[i].first, edges[i].second}) {
        bcc_to_nodes[bccid].insert(node);
        node_to_bccs[node].insert(bccid);
      }
    }
    // testing commented loops in block_vertex_tree
    for (int u = 0; u < n; u++) {
      assert(ssize(node_to_bccs[u]) == ssize(bvt[u]));
      for (auto bccid : bvt[u]) {
        bccid -= n;
        assert(node_to_bccs[u].count(bccid));
      }
    }
    for (int bccid = 0; bccid < cc.num_bccs; bccid++) {
      assert(ssize(bcc_to_nodes[bccid]) == ssize(bvt[bccid + n]));
      for (auto u : bvt[bccid + n])
        assert(bcc_to_nodes[bccid].count(u));
    }
  }
  vector<int> lone_nodes;
  for (int u = 0; u < n; u++)
    if (empty(bvt[u]))
      lone_nodes.push_back(u);
  cout << cc.num_bccs + ssize(lone_nodes) << '\n';
  for (int bccid = 0; bccid < cc.num_bccs; bccid++) {
    cout << ssize(bvt[bccid + n]) << " ";
    for (auto u : bvt[bccid + n])
      cout << u << " ";
    cout << '\n';
  }
  for (auto u : lone_nodes)
    cout << "1 " << u << '\n';
  return 0;
}
