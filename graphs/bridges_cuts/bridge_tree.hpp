//! https://cp-algorithms.com/graph/bridge-searching.html
//! @code
//!   vector<vector<pii>> adj_br(n);
//!   rep (i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     adj_br[u].emplace_back(v, i);
//!     adj_br[v].emplace_back(u, i);
//!   }
//!   auto [num_ccs, is_bridge, br_id] =
//!     bridges(adj_br, m);
//! @endcode
//! is_bridge[edge id] = 1 iff bridge edge
//! br_id[v] = id, 0<=id<num_ccs
//! @time O(n + m)
//! @space O(n + m)
struct bridges {
  int num_ccs = 0;
  vector<bool> is_bridge;
  vector<int> br_id;
  bridges(const vector<vector<pair<int, int>>>& adj,
    int m): is_bridge(m), br_id((int)size(adj), -1) {
    int n = (int)size(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int v, int p_id) -> int {
      int low = tin[v] = timer++, siz = (int)size(st);
      st.push_back(v);
      for (auto [u, e_id] : adj[v]) {
        if (e_id == p_id) continue;
        if (!tin[u]) low = min(low, self(self, u, e_id));
        low = min(low, tin[u]);
      }
      if (tin[v] == low) {
        if (p_id != -1) is_bridge[p_id] = 1;
        for (int i = siz; i < ((int)size(st)); i++)
          br_id[st[i]] = num_ccs;
        st.resize(siz);
        num_ccs++;
      }
      return low;
    };
    for (int i = 0; i < (n); i++)
      if (!tin[i]) dfs(dfs, i, -1);
  }
};
//! @code
//!   bridges br(adj_br, m);
//!   vector<vi> bt = bridge_tree(adj_br, br);
//! @endcode
//! @time O(n + m)
//! @space O(n)
vector<vector<int>> bridge_tree(
  const vector<vector<pair<int, int>>>& adj,
  const bridges& br) {
  vector<vector<int>> tree(br.num_ccs);
  for (int i = 0; i < ((int)size(adj)); i++)
    for (auto [u, e_id] : adj[i])
      if (br.is_bridge[e_id])
        tree[br.br_id[i]].push_back(br.br_id[u]);
  return tree;
}
