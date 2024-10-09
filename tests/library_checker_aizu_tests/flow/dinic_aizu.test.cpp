#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"
#include "../template.hpp"
#include "../../../library/flow/dinic.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  Dinic d(n);
  vector<int> edge_ids(m);
  for (int i = 0; i < m; i++) {
    int u, v, cap;
    cin >> u >> v >> cap;
    edge_ids[i] = d.addEdge(u, v, cap);
  }
  cout << d.calc(0, n - 1) << '\n';
  return 0;
}
