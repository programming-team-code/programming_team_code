#pragma once
#include "../../library/data_structures/rmq.hpp"
#include "../../library/data_structures/uncommon/permutation_tree.hpp"
perm_tree perm_tree_asserts(const vector<int>& a) {
  int n = sz(a);
  perm_tree pt(a);
  {
    vector<int> a_reverse(rbegin(a), rend(a));
    perm_tree pt_reverse(a_reverse);
    queue<pair<int, int>> q;
    q.push({pt.root, pt_reverse.root});
    while (!empty(q)) {
      auto [u, u_reverse] = q.front();
      q.pop();
      assert(sz(pt.adj[u]) ==
             sz(pt_reverse.adj[u_reverse]));
      assert(pt.t[u].is_join ==
             pt_reverse.t[u_reverse].is_join);
      assert(
        pt.t[u].len == pt_reverse.t[u_reverse].len);
      assert(pt.t[u].mn_num ==
             pt_reverse.t[u_reverse].mn_num);
      assert(pt.t[u].mn_idx ==
             n - (pt_reverse.t[u_reverse].mn_idx +
                   pt_reverse.t[u_reverse].len));
      for (int i = 0; i < sz(pt.adj[u]); i++)
        q.push({pt.adj[u][i],
          pt_reverse
            .adj[u_reverse]
                [sz(pt_reverse.adj[u_reverse]) - i -
                  1]});
    }
  }
  RMQ rmq_min(
    a, [](int x, int y) { return min(x, y); });
  RMQ rmq_max(
    a, [](int x, int y) { return max(x, y); });
  auto root = pt.root;
  auto adj = pt.adj;
  assert(pt.t[root].mn_idx == 0 &&
         pt.t[root].mn_num == 0 &&
         pt.t[root].len == n);
  if (n == 1) assert(sz(adj) == 1);
  else assert(n + 1 <= sz(adj) && sz(adj) < 2 * n);
  for (int u = 0; u < sz(adj); u++) {
    {
      int mn_num_rmq = rmq_min.query(pt.t[u].mn_idx,
        pt.t[u].mn_idx + pt.t[u].len);
      assert(mn_num_rmq == pt.t[u].mn_num);
      int mx_num_rmq = rmq_max.query(pt.t[u].mn_idx,
        pt.t[u].mn_idx + pt.t[u].len);
      assert(
        mx_num_rmq - mn_num_rmq + 1 == pt.t[u].len);
    }
    if (empty(adj[u])) {
      assert(0 <= u && u < n);
      assert(pt.t[u].len == 1);
      assert(u == pt.t[u].mn_idx);
      assert(a[u] == pt.t[u].mn_num);
      assert(!pt.t[u].is_join);
    } else {
      assert(n <= u && u < sz(adj));
      if (pt.t[u].is_join) assert(pt.t[u].len >= 2);
      else assert(pt.t[u].len >= 3);
      assert(sz(adj[u]) >= 2);
      assert(
        pt.t[u].mn_idx == pt.t[adj[u][0]].mn_idx);
      assert(pt.t[u].mn_idx + pt.t[u].len ==
             pt.t[adj[u].back()].mn_idx +
               pt.t[adj[u].back()].len);
      assert(
        pt.t[u].is_join ==
        (pt.t[u].mn_num == pt.t[adj[u][0]].mn_num ||
          pt.t[u].mn_num ==
            pt.t[adj[u].back()].mn_num));
      assert(pt.t[u].is_join ==
             (pt.t[u].mn_num + pt.t[u].len ==
                 pt.t[adj[u][0]].mn_num +
                   pt.t[adj[u][0]].len ||
               pt.t[u].mn_num + pt.t[u].len ==
                 pt.t[adj[u].back()].mn_num +
                   pt.t[adj[u].back()].len));
      for (int i = 1; i < sz(adj[u]); i++) {
        int prev = adj[u][i - 1], curr = adj[u][i];
        assert(pt.t[prev].mn_idx + pt.t[prev].len ==
               pt.t[curr].mn_idx);
        assert(pt.t[u].is_join ==
               pt.touches(prev, curr));
      }
      if (sz(adj[u]) <= 10) {
        for (int i = 0; i < sz(adj[u]); i++) {
          int node_le = adj[u][i];
          int running_min = pt.t[node_le].mn_num;
          int running_max = pt.t[node_le].mn_num +
                            pt.t[node_le].len;
          int running_sum = pt.t[node_le].len;
          for (int j = i + 1; j < sz(adj[u]); j++) {
            int node_ri = adj[u][j];
            running_min = min(
              running_min, pt.t[node_ri].mn_num);
            running_max = max(
              running_max, pt.t[node_ri].mn_num +
                             pt.t[node_ri].len);
            running_sum += pt.t[node_ri].len;
            int mn_num_rmq =
              rmq_min.query(pt.t[node_le].mn_idx,
                pt.t[node_ri].mn_idx +
                  pt.t[node_ri].len);
            int mx_num_rmq =
              rmq_max.query(pt.t[node_le].mn_idx,
                pt.t[node_ri].mn_idx +
                  pt.t[node_ri].len);
            int curr_len = pt.t[node_ri].mn_idx +
                           pt.t[node_ri].len -
                           pt.t[node_le].mn_idx;
            assert(running_min == mn_num_rmq &&
                   running_max == mx_num_rmq + 1 &&
                   running_sum == curr_len);
            assert(running_max - running_min >=
                   curr_len);
            assert(curr_len <= pt.t[u].len);
            if (curr_len == pt.t[u].len)
              assert(running_max - running_min ==
                     curr_len);
            else
              assert(pt.t[u].is_join ==
                     (running_max - running_min ==
                       curr_len));
          }
        }
      }
      int mn_num_naive = n, mx_num_naive = -1,
          sum_len_naive = 0;
      for (int v : adj[u]) {
        mn_num_naive =
          min(mn_num_naive, pt.t[v].mn_num);
        mx_num_naive = max(mx_num_naive,
          pt.t[v].mn_num + pt.t[v].len);
        sum_len_naive += pt.t[v].len;
      }
      assert(mn_num_naive == pt.t[u].mn_num);
      assert(mx_num_naive ==
             pt.t[u].mn_num + pt.t[u].len);
      assert(sum_len_naive == pt.t[u].len);
    }
  }
  return pt;
}
