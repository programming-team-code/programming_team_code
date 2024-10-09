#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"
#include "../template.hpp"
#include "../../../library/flow/dinic.hpp"
#include "../dinic_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  dinic d(n);
  vector<int> edge_ids(m);
  vector<array<int, 3>> all_edges(m);
  for (int i = 0; i < m; i++) {
    int u, v, cap;
    cin >> u >> v >> cap;
    all_edges[i] = {u, v, cap};
    edge_ids[i] = d.add_edge(u, v, cap);
  }
  ll total_flow = d.calc(0, n - 1);
  dinic_asserts(d, 0, n - 1, total_flow);
  cout << total_flow << '\n';
  return 0;
}
