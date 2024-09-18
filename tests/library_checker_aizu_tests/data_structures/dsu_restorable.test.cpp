#define PROBLEM \
  "https://judge.yosupo.jp/problem/persistent_unionfind"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/dsu_restorable.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> childs(q + 1), queries(q + 1);
  vector<int> query_u(q + 1), query_v(q + 1);
  for (int i = 1; i <= q; i++) {
    int type, k;
    cin >> type >> k >> query_u[i] >> query_v[i];
    k++;
    if (type == 0) childs[k].push_back(i);
    else {
      assert(type == 1);
      queries[k].push_back(i);
    }
  }
  vector<int> res(q + 1, -1);
  {
    dsu_restorable dsu(n);
    auto dfs = [&](auto&& self, int u) -> void {
      for (auto idx : queries[u])
        res[idx] = dsu.same_set(query_u[idx], query_v[idx]);
      for (auto child : childs[u]) {
        dsu.join(query_u[child], query_v[child]);
        self(self, child);
        dsu.undo();
      }
    };
    dfs(dfs, 0);
  }
  for (int i = 1; i <= q; i++)
    if (res[i] != -1) cout << res[i] << "\n";
  return 0;
}
