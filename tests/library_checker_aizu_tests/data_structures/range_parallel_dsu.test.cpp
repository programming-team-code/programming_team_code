#define PROBLEM "https://judge.yosupo.jp/problem/range_parallel_unionfind"

#include "../template.hpp"
// don't reorder
#include "../../../library/data_structures/dsu/range_parallel_dsu.hpp"
#include "../../../library/math/mod_int.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  range_parallel_dsu dsu(n);
  vector<mint> x(n);
  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;
    x[i] = num;
  }
  mint ans = 0;
  auto f = [&](int u, int v) {
    ans = ans + x[u] * x[v];
    x[u] = x[u] + x[v];
  };
  while (q--) {
    int k, a, b;
    cin >> k >> a >> b;
    dsu.join(a, b, k, f);
    cout << ans.x << '\n';
  }
  return 0;
}
