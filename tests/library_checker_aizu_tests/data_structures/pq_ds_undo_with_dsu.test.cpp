#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "dynamic_graph_vertex_add_component_sum"
// since _GLIBCXX_DEBUG causes std::map insert/erase
// operations to be O(n)
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/data_structures/dsu/dsu_restorable.hpp"
#include "../../../library/data_structures/uncommon/priority_queue_of_updates.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> initial_values(n);
  for (int i = 0; i < n; i++) cin >> initial_values[i];
  vector<int> time_remove(q, -1);
  struct query {
    int type, u, v, x;
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
        queries[i] = {type, u, v, -1};
      } else if (type == 1) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        assert(insert_time.count({u, v}));
        time_remove[insert_time[{u, v}]] = i;
        insert_time.erase({u, v});
        queries[i] = {type, -1, -1, -1};
      } else if (type == 2) {
        int v, x;
        cin >> v >> x;
        queries[i] = {type, -1, v, x};
      } else {
        assert(type == 3);
        int v;
        cin >> v;
        queries[i] = {type, -1, v, -1};
      }
    }
  }
  dsu_restorable dsu_r(n);
  pq_updates<dsu_restorable, int, int> pq(dsu_r);
  for (int i = 0; i < n; i++)
    pq.ds.add(i, initial_values[i]);
  int curr_priority_counter = -q;
  for (int i = 0; i < q; i++) {
    int type = queries[i].type;
    if (type == 0) {
      int u = queries[i].u, v = queries[i].v;
      int curr_pri;
      if (time_remove[i] == -1)
        curr_pri = curr_priority_counter--;
      else curr_pri = -time_remove[i];
      pq.push_update(u, v, curr_pri);
    } else if (type == 1) pq.pop_update();
    else if (type == 2) {
      int v = queries[i].v, x = queries[i].x;
      pq.ds.add(v, x);
    } else {
      assert(type == 3);
      int v = queries[i].v;
      cout << pq.ds.sum(v) << '\n';
    }
  }
  return 0;
}
