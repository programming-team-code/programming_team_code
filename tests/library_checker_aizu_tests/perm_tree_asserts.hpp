#pragma once
#include "../../library/data_structures_[l,r)/rmq.hpp"
#include "../../library/data_structures_[l,r)/uncommon/permutation_tree.hpp"
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
      assert(sz(pt.ch[u]) == sz(pt_reverse.ch[u_reverse]));
      assert(pt.p[u].is_join ==
        pt_reverse.p[u_reverse].is_join);
      assert(pt.p[u].len == pt_reverse.p[u_reverse].len);
      assert(
        pt.p[u].mn_num == pt_reverse.p[u_reverse].mn_num);
      assert(pt.p[u].mn_idx ==
        n -
          (pt_reverse.p[u_reverse].mn_idx +
            pt_reverse.p[u_reverse].len));
      for (int i = 0; i < sz(pt.ch[u]); i++)
        q.push({pt.ch[u][i],
          pt_reverse
            .ch[u_reverse]
               [sz(pt_reverse.ch[u_reverse]) - i - 1]});
    }
  }
  RMQ rmq_min(a, [](int x, int y) { return min(x, y); });
  RMQ rmq_max(a, [](int x, int y) { return max(x, y); });
  auto root = pt.root;
  auto ch = pt.ch;
  assert(pt.p[root].mn_idx == 0 &&
    pt.p[root].mn_num == 0 && pt.p[root].len == n);
  if (n == 1) assert(sz(ch) == 1);
  else assert(n + 1 <= sz(ch) && sz(ch) < 2 * n);
  for (int u = 0; u < sz(ch); u++) {
    {
      int mn_num_rmq = rmq_min.query(pt.p[u].mn_idx,
        pt.p[u].mn_idx + pt.p[u].len);
      assert(mn_num_rmq == pt.p[u].mn_num);
      int mx_num_rmq = rmq_max.query(pt.p[u].mn_idx,
        pt.p[u].mn_idx + pt.p[u].len);
      assert(mx_num_rmq - mn_num_rmq + 1 == pt.p[u].len);
    }
    if (empty(ch[u])) {
      assert(0 <= u && u < n);
      assert(pt.p[u].len == 1);
      assert(u == pt.p[u].mn_idx);
      assert(a[u] == pt.p[u].mn_num);
      assert(!pt.p[u].is_join);
    } else {
      assert(n <= u && u < sz(ch));
      if (pt.p[u].is_join) assert(pt.p[u].len >= 2);
      else assert(pt.p[u].len >= 3);
      assert(sz(ch[u]) >= 2);
      assert(pt.p[u].mn_idx == pt.p[ch[u][0]].mn_idx);
      assert(pt.p[u].mn_idx + pt.p[u].len ==
        pt.p[ch[u].back()].mn_idx +
          pt.p[ch[u].back()].len);
      assert(pt.p[u].is_join ==
        (pt.p[u].mn_num == pt.p[ch[u][0]].mn_num ||
          pt.p[u].mn_num == pt.p[ch[u].back()].mn_num));
      assert(pt.p[u].is_join ==
        (pt.p[u].mn_num + pt.p[u].len ==
            pt.p[ch[u][0]].mn_num + pt.p[ch[u][0]].len ||
          pt.p[u].mn_num + pt.p[u].len ==
            pt.p[ch[u].back()].mn_num +
              pt.p[ch[u].back()].len));
      for (int i = 1; i < sz(ch[u]); i++) {
        int prev = ch[u][i - 1], curr = ch[u][i];
        assert(pt.p[prev].mn_idx + pt.p[prev].len ==
          pt.p[curr].mn_idx);
        assert(pt.p[u].is_join == pt.touches(prev, curr));
      }
      if (sz(ch[u]) <= 10) {
        for (int i = 0; i < sz(ch[u]); i++) {
          int node_le = ch[u][i];
          int running_min = pt.p[node_le].mn_num;
          int running_max =
            pt.p[node_le].mn_num + pt.p[node_le].len;
          int running_sum = pt.p[node_le].len;
          for (int j = i + 1; j < sz(ch[u]); j++) {
            int node_ri = ch[u][j];
            running_min =
              min(running_min, pt.p[node_ri].mn_num);
            running_max = max(running_max,
              pt.p[node_ri].mn_num + pt.p[node_ri].len);
            running_sum += pt.p[node_ri].len;
            int mn_num_rmq =
              rmq_min.query(pt.p[node_le].mn_idx,
                pt.p[node_ri].mn_idx + pt.p[node_ri].len);
            int mx_num_rmq =
              rmq_max.query(pt.p[node_le].mn_idx,
                pt.p[node_ri].mn_idx + pt.p[node_ri].len);
            int curr_len = pt.p[node_ri].mn_idx +
              pt.p[node_ri].len - pt.p[node_le].mn_idx;
            assert(running_min == mn_num_rmq &&
              running_max == mx_num_rmq + 1 &&
              running_sum == curr_len);
            assert(running_max - running_min >= curr_len);
            assert(curr_len <= pt.p[u].len);
            if (curr_len == pt.p[u].len)
              assert(
                running_max - running_min == curr_len);
            else
              assert(pt.p[u].is_join ==
                (running_max - running_min == curr_len));
          }
        }
      }
      int mn_num_naive = n, mx_num_naive = -1,
          sum_len_naive = 0;
      for (int v : ch[u]) {
        mn_num_naive = min(mn_num_naive, pt.p[v].mn_num);
        mx_num_naive =
          max(mx_num_naive, pt.p[v].mn_num + pt.p[v].len);
        sum_len_naive += pt.p[v].len;
      }
      assert(mn_num_naive == pt.p[u].mn_num);
      assert(mx_num_naive == pt.p[u].mn_num + pt.p[u].len);
      assert(sum_len_naive == pt.p[u].len);
    }
  }
  return pt;
}
