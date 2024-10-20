#define PROBLEM \
  "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/dsu_restorable.hpp"
#include "../../../library/data_structures/lazy_seg_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  dsu_restorable dsu(n);
  for (int i = 0; i < n; i++) cin >> dsu.subtree[i];
  vector<vector<pair<int, int>>> tree(2 * q);
  auto add_edge = [&](auto&& self, int l, int r,
                    int node_u, int node_v, int tl, int tr,
                    int v) -> void {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) {
      tree[v].emplace_back(node_u, node_v);
      return;
    }
    int tm = split(tl, tr);
    self(self, l, r, node_u, node_v, tl, tm, 2 * v);
    self(self, l, r, node_u, node_v, tm, tr, 2 * v + 1);
  };
  struct query {
    int type, v, x;
  };
  vector<query> queries(q);
  {
    map<pair<int, int>, int> insert_time;
    for (int i = 0; i < q; i++) {
      int type;
      cin >> type;
      if (type == 0) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        assert(!insert_time.count({u, v}));
        insert_time[{u, v}] = i;
      } else if (type == 1) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        assert(insert_time.count({u, v}));
        add_edge(add_edge, insert_time[{u, v}], i, u, v, 0,
          q, 1);
        insert_time.erase({u, v});
      } else if (type == 2) {
        int v, x;
        cin >> v >> x;
        queries[i] = {2, v, x};
      } else {
        assert(type == 3);
        int v;
        cin >> v;
        queries[i] = {3, v, -1};
      }
    }
    for (auto [edge, i_time] : insert_time)
      add_edge(add_edge, i_time, q, edge.first,
        edge.second, 0, q, 1);
  }
  auto dfs = [&](auto&& self, int tl, int tr,
               int v) -> void {
    for (auto [node_u, node_v] : tree[v])
      dsu.join(node_u, node_v);
    assert((v >= q) == ((tr - tl) == 1));
    if (v >= q) { // leaf node
      const int depth_leaf = __lg(v),
                max_depth = __lg(2 * q - 1);
      if (tl == 0) { // left-most leaf
        assert(v == (1 << max_depth));
        assert(depth_leaf == max_depth);
      }
      assert(q <= v && v < 2 * q);
      assert(depth_leaf == max_depth ||
        depth_leaf == max_depth - 1);
      if ((q & (q - 1)) == 0)
        assert(depth_leaf == max_depth);
      if (queries[tl].type == 2)
        dsu.add(queries[tl].v, queries[tl].x);
      else if (queries[tl].type == 3)
        cout << dsu.sum(queries[tl].v) << '\n';
    } else {
      assert(1 <= v && v < q);
      if (((tr - tl) & (tr - tl - 1)) == 0)
        assert(split(tl, tr) == (tl + tr) / 2);
      {
        int pow_2 = 1 << __lg(tr - tl);
        if (tl + pow_2 < tr - pow_2 / 2) {
          assert(pow_2 != tr - tl);
          assert(pow_2 / 2 < tr - tl - pow_2 &&
            tr - tl - pow_2 < pow_2);
          assert(pow_2 <= 2 * (tr - tl - pow_2) - 1 &&
            2 * (tr - tl - pow_2) - 1 < 2 * pow_2 - 1);
          assert(__lg(pow_2) ==
              __lg(2 * ((tr - tl) - pow_2) - 1) &&
            __lg(pow_2) == __lg(2 * pow_2 - 1));
        } else if (pow_2 < tr - tl) {
          assert(pow_2 / 2 < tr - tl - pow_2 / 2 &&
            tr - tl - pow_2 / 2 <= pow_2);
          assert(
            pow_2 <= 2 * ((tr - tl) - pow_2 / 2) - 1 &&
            2 * ((tr - tl) - pow_2 / 2) - 1 <=
              2 * pow_2 - 1);
          assert(__lg(2 * (tr - tl - pow_2 / 2) - 1) ==
            __lg(2 * pow_2 - 1));
          assert(__lg(2 * ((tr - tl) - pow_2 / 2) - 1) ==
            __lg(pow_2));
          assert(
            __lg(pow_2) == 1 + __lg(2 * (pow_2 / 2) - 1));
        }
      }
      int tm = split(tl, tr);
      // in particular, this tests that split works with
      // negatives
      assert(split(tl - 1234, tr - 1234) == tm - 1234);
      assert(split(tl - 1, tr - 1) == tm - 1);
      assert(split(tl + 50, tr + 50) == tm + 50);
      self(self, tl, tm, 2 * v);
      self(self, tm, tr, 2 * v + 1);
    }
    for (int i = 0; i < sz(tree[v]); i++) dsu.undo();
  };
  dfs(dfs, 0, q, 1);
  return 0;
}
