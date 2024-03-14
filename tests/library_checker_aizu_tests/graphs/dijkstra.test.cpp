#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"
// since this causes an O(n) heap-property check for each call to
//`priority_queue::push`, causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/graphs/dijkstra.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m, s;
  cin >> n >> m >> s;
  vector<vector<pair<int, int64_t>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
  }
  vector<int64_t> len = dijkstra(adj, s);
  for (int i = 0; i < n; i++) {
    if (len[i] == LLONG_MAX)
      cout << "INF\n";
    else
      cout << len[i] << '\n';
  }
  return 0;
}
