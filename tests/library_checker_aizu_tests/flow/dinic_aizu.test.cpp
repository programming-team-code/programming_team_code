#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"
#include "../template.hpp"
#include "../../../library/flow/dinic.hpp"
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
  ll flow = d.calc(0, n - 1);
  cout << flow << '\n';
  vector<ll> in_flow(n), out_flow(n);
  for (int i = 0; i < m; i++) {
    dinic::edge e = d.edges[edge_ids[i]];
    out_flow[all_edges[i][0]] += e.flow();
    in_flow[e.to] += e.flow();
    assert(0 <= e.flow() && e.flow() <= all_edges[i][2]);
  }
  assert(in_flow[0] == 0);
  assert(out_flow[0] == flow);
  assert(in_flow[n - 1] == flow);
  assert(out_flow[n - 1] == 0);
  for (int i = 1; i < n - 1; i++)
    assert(in_flow[i] == out_flow[i]);
  {
    queue<int> q;
    q.push(0);
    vector<bool> vis(n);
    vis[0] = 1;
    while (!empty(q)) {
      int v = q.front();
      q.pop();
      for (int id : d.adj[v]) {
        dinic::edge e = d.edges[id];
        if (e.flow() == e.cap) continue;
        int u = e.to;
        if (!vis[u]) {
          vis[u] = 1;
          q.push(u);
        }
      }
    }
    for (int i = 0; i < n; i++)
      assert(vis[i] == d.left_of_min_cut(i));
  }
  return 0;
}
