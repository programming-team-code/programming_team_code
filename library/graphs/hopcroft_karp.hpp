#pragma once
//! https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
//! @code
//!   adj[le].push_back(ri); // add edge le <-> ri
//!   auto [m_sz, to_r, to_l,
//!     mvc_l, mvc_r] = hopcroft_karp(adj, rsz);
//! @endcode
//! 0<=le<lsz; 0<=ri<rsz
//! le <-> to_r[le] in matching if to_r[le]!=-1
//! to_l[ri] <-> ri in matching if to_l[ri]!=-1
//! mvc_l[le] is true if le in MVC
//! mvc_r[ri] is true if ri in MVC
//! @time O(n + m * sqrt(n)) n = lsz + rsz
//! @space O(n)
struct hopcroft_karp {
  int m_sz = 0;
  vi to_r, to_l;
  vector<bool> mvc_l, mvc_r;
  hopcroft_karp(const vector<vi>& adj, int rsz):
    to_r(sz(adj), -1), to_l(rsz, -1) {
    int lsz = sz(adj);
    while (1) {
      queue<int> q;
      vector level(lsz, -1);
      rep(i, 0, lsz) if (to_r[i] == -1) level[i] = 0,
                                        q.push(i);
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
      rep(i, 0, lsz) m_sz +=
        (to_r[i] == -1 && dfs(dfs, i));
    }
  }
};
