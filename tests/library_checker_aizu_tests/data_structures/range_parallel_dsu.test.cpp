#define PROBLEM \
  "https://judge.yosupo.jp/problem/range_parallel_unionfind"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/range_parallel_dsu.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/dsu/range_parallel_equivalence_classes.hpp"
#include "../../../library/math/mod_int.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  range_parallel_dsu dsu(n);
  vector<mint> y(n);
  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;
    y[i] = num;
  }
  vector<mint> x = y;
  mint ans = 0;
  auto f = [&](int u, int v) {
    ans = ans + x[u] * x[v];
    x[u] = x[u] + x[v];
  };
  vector<array<int, 3>> queries;
  for (int qq = 0; qq < q; qq++) {
    int k, a, b;
    cin >> k >> a >> b;
    dsu.join(a, b, k, f);
    queries.push_back({a, b, k});
    cout << ans.x << '\n';
    if (qq <= 10 || abs(q - qq) <= 10 ||
      rnd(0, 50'000) == 0) {
      auto uf =
        get_range_parallel_equivalence_classes(queries, n);
      vector<mint> sums(n);
      mint offline_ans = 0;
      for (int i = 0; i < n; i++) {
        int id = uf.find(i);
        offline_ans = offline_ans + sums[id] * y[i];
        sums[id] = sums[id] + y[i];
      }
      assert(ans.x == offline_ans.x);
    }
  }
  return 0;
}
