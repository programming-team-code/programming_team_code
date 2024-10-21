//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//! @code
//!   auto [num_sccs, scc_id] = sccs(adj);
//! @endcode
//! scc_id[v] = id, 0<=id<num_sccs
//! for each edge u -> v: scc_id[u] >= scc_id[v]
//! @time O(n + m)
//! @space O(n)
struct sccs {
  int num_sccs = 0;
  vector<int> scc_id;
  sccs(const vector<vector<int>>& adj):
    scc_id(ssize(adj), -1) {
    int n = ssize(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int v) -> int {
      int low = tin[v] = timer++, siz = ssize(st);
      st.push_back(v);
      for (int u : adj[v])
        if (scc_id[u] < 0)
          low = min(low, tin[u] ? tin[u] : self(self, u));
      if (tin[v] == low) {
        for (int i = siz; i < ssize(st); i++)
          scc_id[st[i]] = num_sccs;
        st.resize(siz);
        num_sccs++;
      }
      return low;
    };
    for (int i = 0; i < n; i++)
      if (!tin[i]) dfs(dfs, i);
  }
};
//! https://codeforces.com/blog/entry/91608
//! @code
//!   auto joins = offline_incremental_scc(eds, n);
//! @endcode
//! joins[i] = minimum prefix of edges [0, joins[i]] for
//!   eds[i][0] and eds[i][1] to be in the same SCC
//! joins[i] = m if they're never in the same SCC
//! joins[i] = -1 if eds[i][0] == eds[i][1]
//! @time O((n + m) log m)
//! @space O(n + m)
vector<int> offline_incremental_scc(
  vector<array<int, 2>> eds, int n) {
  int m = ssize(eds);
  vector<int> ids(n, -1), joins(m, m), idx(m);
  iota(begin(idx), end(idx), 0);
  auto divide_and_conquer = [&](auto&& self, auto el,
                              auto er, int tl, int tr) {
    int mid = tl + (tr - tl) / 2;
    vector<int> vs;
    vector<vector<int>> adj;
    for (auto it = el; it != er; it++) {
      auto& [u, v] = eds[*it];
      for (int w : {u, v}) {
        if (ids[w] != -1) continue;
        ids[w] = ssize(vs);
        vs.push_back(w);
        adj.emplace_back();
      }
      u = ids[u], v = ids[v];
      if (*it <= mid) adj[u].push_back(v);
    }
    for (int v : vs) ids[v] = -1;
    auto scc_id = sccs(adj).scc_id;
    auto split = partition(el, er, [&](int i) {
      return scc_id[eds[i][0]] == scc_id[eds[i][1]];
    });
    for (auto it = el; it != split; it++) joins[*it] = mid;
    if (tr - tl == 1) return;
    for (auto it = split; it != er; it++) {
      auto& [u, v] = eds[*it];
      u = scc_id[u], v = scc_id[v];
    }
    // deallocate to avoid O(m log m) memory
    vector<int>().swap(vs);
    vector<vector<int>>().swap(adj);
    vector<int>().swap(scc_id);
    self(self, el, split, tl, mid);
    self(self, split, er, mid, tr);
  };
  // uses -1 as the lower bound to correctly handle
  // self-edges
  divide_and_conquer(divide_and_conquer, begin(idx),
    end(idx), -1, m);
  return joins;
}
