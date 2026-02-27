//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//! @code
//!   vector<basic_string<int>> adj(n);
//!   auto [num_sccs, scc_id] = scc(adj);
//! @endcode
//! scc_id[u] = id, 0<=id<num_sccs
//! for each edge u -> v: scc_id[u] >= scc_id[v]
//! @time O(n + m)
//! @space O(n)
auto scc(const auto& adj) {
  int n = ssize(adj), num_sccs = 0, q = 0, s = 0;
  vector<int> scc_id(n, -1), tin(n), st(n);
  auto dfs = [&](auto&& self, int u) -> int {
    int low = tin[u] = ++q;
    st[s++] = u;
    for (int v : adj[u])
      if (scc_id[v] < 0)
        low = min(low, tin[v] ?: self(self, v));
    if (tin[u] == low) {
      while (scc_id[u] < 0) scc_id[st[--s]] = num_sccs;
      num_sccs++;
    }
    return low;
  };
  for (int i = 0; i < n; i++)
    if (!tin[i]) dfs(dfs, i);
  return pair{num_sccs, scc_id};
}
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
  vector<int> ids(n, -1), joins(m, m), idx(m), vs(n),
    scc_id;
  iota(begin(idx), end(idx), 0);
  vector<vector<int>> adj;
  auto divide_and_conquer = [&](auto&& self, auto el,
                              auto er, int tl, int tr) {
    adj.clear();
    int mid = midpoint(tl, tr);
    for (auto it = el; it != er; it++) {
      auto& [u, v] = eds[*it];
      for (int w : {u, v}) {
        if (ids[w] != -1) continue;
        ids[w] = ssize(adj);
        vs[ssize(adj)] = w;
        adj.emplace_back();
      }
      u = ids[u], v = ids[v];
      if (*it <= mid) adj[u].push_back(v);
    }
    for (int i = 0; i < ssize(adj); i++) ids[vs[i]] = -1;
    scc_id = scc(adj).second;
    auto split = partition(el, er, [&](int i) {
      return scc_id[eds[i][0]] == scc_id[eds[i][1]];
    });
    for (auto it = el; it != split; it++) joins[*it] = mid;
    if (tr - tl == 1) return;
    for (auto it = split; it != er; it++) {
      auto& [u, v] = eds[*it];
      u = scc_id[u], v = scc_id[v];
    }
    self(self, el, split, tl, mid);
    self(self, split, er, mid, tr);
  };
  // uses -1 as the lower bound to correctly handle
  // self-edges
  divide_and_conquer(divide_and_conquer, begin(idx),
    end(idx), -1, m);
  return joins;
}
