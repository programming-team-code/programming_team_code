#define PROBLEM \
  "https://judge.yosupo.jp/problem/range_parallel_unionfind"
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/dsu/range_parallel_dsu.hpp"
#include "../../../library/dsu/range_parallel_equivalence_classes.hpp"
const int mod = 998244353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  rp_dsu dsu(n);
  vi y(n);
  for (int i = 0; i < n; i++) cin >> y[i];
  vi x = y;
  int ans = 0;
  auto f = [&](int u, int v) {
    ans = (ans + 1LL * x[u] * x[v]) % mod;
    x[u] = (x[u] + x[v]) % mod;
  };
  vector<vector<pii>> joins(n + 1);
  for (int qq = 0; qq < q; qq++) {
    int k, a, b;
    cin >> k >> a >> b;
    if (k) dsu.join(a, b, k, f);
    joins[k].emplace_back(a, b);
    cout << ans << '\n';
    if (qq == 0 || qq == 1 || qq == 10 || qq == 1000 ||
      qq == 100'000 || qq == q - 1) {
      auto uf = get_rp_dsu(joins, n);
      vi sums(n);
      int offline_ans = 0;
      for (int i = 0; i < n; i++) {
        int id = uf.f(i);
        offline_ans =
          (offline_ans + 1LL * sums[id] * y[i]) % mod;
        sums[id] = (sums[id] + y[i]) % mod;
      }
      assert(ans == offline_ans);
    }
  }
  return 0;
}
