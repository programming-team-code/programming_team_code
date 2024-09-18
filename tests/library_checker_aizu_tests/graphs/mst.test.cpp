#define PROBLEM \
  "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include "../template.hpp"
#include "../../../library/graphs/mst.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<array<int, 3>> eds(m);
  for (auto& [u, v, w] : eds) cin >> u >> v >> w;
  auto [cost, ids] = mst(eds, n);
  cout << cost << '\n';
  for (int id : ids) cout << id << ' ';
  cout << '\n';
  return 0;
}
