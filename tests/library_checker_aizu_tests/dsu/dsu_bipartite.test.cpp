#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../template.hpp"
#include "../../../library/dsu/dsu_bipartite.hpp"
#include "../../../library/contest/random.hpp"
vector<bool> bipartite_check(const vector<vi>& adj) {
  int n = sz(adj);
  vector<bool> is_bi(n);
  vi color(n, -1);
  rep(s, 0, n) {
    if (color[s] != -1) continue;
    color[s] = 0;
    vi q{s};
    bool is_bipartite = 1;
    rep(fr, 0, sz(q)) {
      int u = q[fr];
      for (int v : adj[u])
        if (color[v] == -1) {
          color[v] = color[u] ^ 1;
          q.push_back(v);
        } else is_bipartite &= color[v] != color[u];
    }
    for (int u : q) is_bi[u] = is_bipartite;
  }
  return is_bi;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  dsu_bipartite dsu(n);
  vector<vi> adj(n);
  auto check = [&]() {
    vector<bool> is_bi = bipartite_check(adj);
    rep(s, 0, n) assert(dsu.is_bipartite(s) == is_bi[s]);
  };
  rep(i, 0, q) {
    int t, u, v;
    cin >> t >> u >> v;
    if (t == 0) {
      dsu.join(u, v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    } else cout << (dsu.f(u) == dsu.f(v)) << '\n';
    if (i <= 20 || rnd<int>(0, 20'000) == 0) check();
  }
  check();
  return 0;
}
