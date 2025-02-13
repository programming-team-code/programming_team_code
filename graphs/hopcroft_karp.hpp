//! https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
//! @code
//!   {
//!     vector<vi> adj(lsz);
//!     auto [matching_size, to_r, to_l,
//!       mvc_l, mvc_r] = hopcroft_karp(adj, rsz);
//!   }
//!   vector<basic_string<int>> adj(lsz);
//!   adj[l] += r; // add edge l <-> r
//!                        // 0<=l<lsz; 0<=r<rsz
//!   auto [matching_size, to_r, to_l,
//!     mvc_l, mvc_r] = hopcroft_karp(adj, rsz);
//! @endcode
//! l <-> to_r[l] in matching if to_r[l]!=-1
//! to_l[r] <-> r in matching if to_l[r]!=-1
//! mvc_l[l] is 1 if l in Min Vertex Cover
//! mvc_r[r] is 1 if r in Min Vertex Cover
//! @time O(n + m * sqrt(n)) n = lsz + rsz
//! @space O(n)
struct hopcroft_karp {
  int m_sz = 0;
  vector<int> to_r, to_l;
  vector<bool> mvc_l, mvc_r;
  hopcroft_karp(const auto& adj, int rsz):
    to_r(ssize(adj), -1), to_l(rsz, -1) {
    int lsz = ssize(adj);
    while (1) {
      queue<int> q;
      vector<int> level(lsz, -1);
      for (int i = 0; i < lsz; i++)
        if (to_r[i] == -1) level[i] = 0, q.push(i);
      bool found = 0;
      mvc_l.assign(lsz, 1);
      mvc_r.assign(rsz, 0);
      while (!empty(q)) {
        int v = q.front();
        q.pop();
        mvc_l[v] = 0;
        for (int u : adj[v]) {
          mvc_r[u] = 1;
          int w = to_l[u];
          if (w == -1) found = 1;
          else if (level[w] == -1) {
            level[w] = level[v] + 1;
            q.push(w);
          }
        }
      }
      if (!found) break;
      auto dfs = [&](auto&& self, int v) -> bool {
        for (int u : adj[v]) {
          int w = to_l[u];
          if (w == -1 ||
            (level[v] + 1 == level[w] && self(self, w))) {
            to_r[v] = u;
            to_l[u] = v;
            return 1;
          }
        }
        level[v] = INT_MAX;
        return 0;
      };
      for (int i = 0; i < lsz; i++)
        m_sz += (to_r[i] == -1 && dfs(dfs, i));
    }
  }
};
