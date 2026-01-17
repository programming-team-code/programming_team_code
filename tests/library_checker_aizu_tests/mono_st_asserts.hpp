#pragma once
#include "../../library/monotonic_stack/monotonic_range.hpp"
#include "../../library/monotonic_stack/cartesian_binary_tree.hpp"
#include "../../library/monotonic_stack/cartesian_k_ary_tree.hpp"
#include "../../library/data_structures_[l,r]/linear_rmq.hpp"
tuple<int, vector<vector<int>>, vector<int>>
min_cartesian_tree(const vector<int>& a,
  const vector<int>& l, const vector<int>& r) {
  int n = sz(a);
  assert(sz(l) == n && sz(r) == n);
  auto is_node = [&](int i) -> bool {
    return r[i] == n || a[r[i]] < a[i];
  };
  vector<int> to_min(n);
  iota(begin(to_min), end(to_min), 0);
  for (int i = n - 1; i >= 0; i--)
    if (!is_node(i)) to_min[i] = to_min[r[i]];
  vector<vector<int>> adj(n);
  int root = -1;
  for (int i = 0; i < n; i++) {
    if (l[i] == -1 && r[i] == n) {
      assert(root == -1);
      root = i;
    } else if (is_node(i)) {
      bool le_par =
        (l[i] >= 0 && (r[i] == n || a[l[i]] > a[r[i]]));
      adj[to_min[le_par ? l[i] : r[i]]].push_back(i);
    }
  }
  return {root, adj, to_min};
}
void mono_st_asserts(const vector<int>& a) {
  vector<function<bool(int, int)>> compares;
  compares.push_back(less());
  compares.push_back(less_equal());
  compares.push_back(greater());
  compares.push_back(greater_equal());
  int n = sz(a);
  for (auto cmp : compares) {
    auto l = mono_st(a, cmp), r = mono_range(l),
         p = cart_binary_tree(l);
    {
      vector old_way_ri = mono_st(vi{rbegin(a), rend(a)},
        [&](int x, int y) { return !cmp(y, x); });
      reverse(begin(old_way_ri), end(old_way_ri));
      transform(begin(old_way_ri), end(old_way_ri),
        begin(old_way_ri),
        [&](int i) { return sz(a) - i - 1; });
      assert(r == old_way_ri);
    }
    int iterations = 0;
    for (int i = n - 1; i >= 0; i--) {
      assert(i < r[i] && r[i] <= n);
      assert(r[i] == n || !cmp(a[i], a[r[i]]));
      for (int j = i + 1; j != r[i]; j = r[j]) {
        // for all k in [j, r[j]): cmp(a[i], a[k])
        // these ranges are disjoint, and union to [i + 1,
        // r[i])
        assert(j <= r[i]);
        assert(cmp(a[i], a[j]));
        assert(cmp(a[i], a[r[j] - 1]));
        assert(cmp(a[i], a[j + (r[j] - j) / 2]));
        iterations++;
      }
    }
    // clear the stack
    for (int j = 0; j != n; j = r[j]) iterations++;
    assert(iterations == n);
  }
  // test cartesian tree against old method
  auto l = mono_st(a, less()), r = mono_range(l),
       p = cart_k_ary_tree(a, l);
  assert(count(begin(p), end(p), -1) == !empty(a));
  for (int i = 0; i < n; i++)
    assert(-1 <= p[i] && p[i] < n && p[i] != i);
  auto [root, adj, to_min] = min_cartesian_tree(a, l, r);
  vector<int> p_old_method(n, -2);
  auto set_val = [&](int i, int val) -> void {
    assert(p_old_method[i] == -2);
    p_old_method[i] = val;
  };
  assert((root == -1) == empty(a));
  if (root != -1) set_val(root, -1);
  for (int i = 0; i < n; i++)
    for (int j : adj[i]) set_val(j, i);
  for (int i = 0; i < n; i++)
    if (to_min[i] > i) set_val(i, to_min[i]);
  assert(p == p_old_method);
}
