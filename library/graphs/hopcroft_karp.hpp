/** @file */
#pragma once
/**
 * @see https://github.com/foreverbell/acm-icpc-cheat-sheet /blob/master/src/graph-algorithm/hopcroft-karp.cpp
 * @code{.cpp}
       //0 <= node_left < lsz
       //0 <= node_right < rsz
       //for every edge node_left <=> node_right
       adj[node_left].push_back(node_right);
       auto [size_of_matching, l_to_r, r_to_l, mvc_l, mvc_r] = hopcroft_karp(adj, rsz);
 * @endcode
 */
struct hopcroft_karp {
  int size_of_matching = 0; /**< # of edges in max matching (which = size of min vertex cover by König's theorem) */
  /**
   * edge node_left <=> l_to_r[node_left] in matching iff l_to_r[node_left] != -1
   * ditto r_to_l[node_right] <=> node_right
   * @{
   */
  vector<int> l_to_r, r_to_l;
  /** @} */
  /**
   * mvc_l[node_left] = 1 iff node_left is in the min vertex cover; ditto mvc_r[node_right]
   * mvc_l[node_left] = 0 iff node_left is in the max independent set
   * @{
   */
  vector<bool> mvc_l, mvc_r;
  /** @} */
  /**
   * @param adj bipartite graph
   * @param rsz number of nodes on right side
   * @time O(n + m * sqrt(n)) n = lsz + rsz
   * @space this allocates member vectors which are O(lsz + rsz)
   */
  hopcroft_karp(const vector<vector<int>>& adj, int rsz) : l_to_r(ssize(adj), -1), r_to_l(rsz, -1) {
    int lsz = ssize(adj);
    while (1) {
      queue<int> q;
      vector level(lsz, -1);
      for (int i = 0; i < lsz; i++)
        if (l_to_r[i] == -1) level[i] = 0, q.push(i);
      bool found = 0;
      mvc_l.assign(lsz, 1);
      mvc_r.assign(rsz, 0);
      while (!empty(q)) {
        int u = q.front();
        q.pop();
        mvc_l[u] = 0;
        for (int v : adj[u]) {
          mvc_r[v] = 1;
          int w = r_to_l[v];
          if (w == -1) found = 1;
          else if (level[w] == -1) {
            level[w] = level[u] + 1;
            q.push(w);
          }
        }
      }
      if (!found) break;
      auto dfs = [&](auto&& self, int u) -> bool {
        for (int v : adj[u]) {
          int w = r_to_l[v];
          if (w == -1 || (level[u] + 1 == level[w] && self(self, w))) {
            l_to_r[u] = v;
            r_to_l[v] = u;
            return 1;
          }
        }
        level[u] = INT_MAX;
        return 0;
      };
      for (int i = 0; i < lsz; i++)
        size_of_matching += (l_to_r[i] == -1 && dfs(dfs, i));
    }
  }
};
