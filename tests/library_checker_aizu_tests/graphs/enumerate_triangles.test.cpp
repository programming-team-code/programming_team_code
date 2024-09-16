#define PROBLEM \
  "https://judge.yosupo.jp/problem/enumerate_triangles"
#include "../template.hpp"

#include "../../../library/graphs/enumerate_triangles.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<int> vals(n);
  for (int i = 0; i < n; i++) cin >> vals[i];
  vector<pair<int, int>> edges(m);
  for (auto& [u, v] : edges) cin >> u >> v;
  const int mod = 998'244'353;
  int64_t sum = 0;
  auto enumerate = [&](int u, int v, int w) {
    sum = (sum +
           1LL * vals[u] * vals[v] % mod * vals[w] % mod) %
          mod;
  };
  enumerate_triangles(edges, n, enumerate);
  cout << sum << '\n';
  return 0;
}
