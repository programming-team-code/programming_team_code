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
      assert(sz(pt.adj[u]) == sz(pt_reverse.adj[u_reverse]));
      assert(pt.is_join[u] == pt_reverse.is_join[u_reverse]);
      assert(pt.len[u] == pt_reverse.len[u_reverse]);
      assert(pt.mn_num[u] == pt_reverse.mn_num[u_reverse]);
      assert(pt.mn_idx[u] == n - (pt_reverse.mn_idx[u_reverse] + pt_reverse.len[u_reverse]));
      for (int i = 0; i < sz(pt.adj[u]); i++)
        q.push({pt.adj[u][i], pt_reverse.adj[u_reverse][sz(pt_reverse.adj[u_reverse]) - i - 1]});
    }
  }
  RMQ rmq_min(a, [](int x, int y) { return min(x, y); });
  RMQ rmq_max(a, [](int x, int y) { return max(x, y); });
  auto is_join = pt.is_join;
  auto mn_idx = pt.mn_idx;
  auto mn_num = pt.mn_num;
  auto len = pt.len;
  auto root = pt.root;
  auto adj = pt.adj;
  assert(mn_idx[root] == 0 && mn_num[root] == 0 && len[root] == n);
  if (n == 1) assert(sz(adj) == 1);
  else assert(n + 1 <= sz(adj) && sz(adj) < 2 * n);
  for (int u = 0; u < sz(adj); u++) {
    {
      int mn_num_rmq = rmq_min.query(mn_idx[u], mn_idx[u] + len[u]);
      assert(mn_num_rmq == mn_num[u]);
      int mx_num_rmq = rmq_max.query(mn_idx[u], mn_idx[u] + len[u]);
      assert(mx_num_rmq - mn_num_rmq + 1 == len[u]);
    }
    if (empty(adj[u])) {
      assert(0 <= u && u < n);
      assert(len[u] == 1);
      assert(u == mn_idx[u]);
      assert(a[u] == mn_num[u]);
      assert(!is_join[u]);
    } else {
      assert(n <= u && u < sz(adj));
      if (is_join[u]) assert(len[u] >= 2);
      else assert(len[u] >= 3);
      assert(sz(adj[u]) >= 2);
      assert(mn_idx[u] == mn_idx[adj[u][0]]);
      assert(mn_idx[u] + len[u] == mn_idx[adj[u].back()] + len[adj[u].back()]);
      assert(is_join[u] == (mn_num[u] == mn_num[adj[u][0]] || mn_num[u] == mn_num[adj[u].back()]));
      assert(is_join[u] == (mn_num[u] + len[u] == mn_num[adj[u][0]] + len[adj[u][0]] ||
                            mn_num[u] + len[u] == mn_num[adj[u].back()] + len[adj[u].back()]));
      for (int i = 1; i < sz(adj[u]); i++) {
        int prev = adj[u][i - 1], curr = adj[u][i];
        assert(mn_idx[prev] + len[prev] == mn_idx[curr]);
        assert(is_join[u] == pt.touches(prev, curr));
      }
      if (sz(adj[u]) <= 10) {
        for (int i = 0; i < sz(adj[u]); i++) {
          int node_le = adj[u][i];
          int running_min = mn_num[node_le];
          int running_max = mn_num[node_le] + len[node_le];
          int running_sum = len[node_le];
          for (int j = i + 1; j < sz(adj[u]); j++) {
            int node_ri = adj[u][j];
            running_min = min(running_min, mn_num[node_ri]);
            running_max = max(running_max, mn_num[node_ri] + len[node_ri]);
            running_sum += len[node_ri];
            int mn_num_rmq = rmq_min.query(mn_idx[node_le], mn_idx[node_ri] + len[node_ri]);
            int mx_num_rmq = rmq_max.query(mn_idx[node_le], mn_idx[node_ri] + len[node_ri]);
            int curr_len = mn_idx[node_ri] + len[node_ri] - mn_idx[node_le];
            assert(running_min == mn_num_rmq && running_max == mx_num_rmq + 1 && running_sum == curr_len);
            assert(running_max - running_min >= curr_len);
            assert(curr_len <= len[u]);
            if (curr_len == len[u]) assert(running_max - running_min == curr_len);
            else assert(is_join[u] == (running_max - running_min == curr_len));
          }
        }
      }
      int mn_num_naive = n, mx_num_naive = -1, sum_len_naive = 0;
      for (int v : adj[u]) {
        mn_num_naive = min(mn_num_naive, mn_num[v]);
        mx_num_naive = max(mx_num_naive, mn_num[v] + len[v]);
        sum_len_naive += len[v];
      }
      assert(mn_num_naive == mn_num[u]);
      assert(mx_num_naive == mn_num[u] + len[u]);
      assert(sum_len_naive == len[u]);
    }
  }
  return pt;
}
