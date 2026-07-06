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
  rp_dsu r_dsu(n);
  vi y(n);
  rep(i, 0, n) cin >> y[i];
  vi x = y;
  int res = 0;
  DSU dsu(n);
  auto f = [&](int u, int v) {
    u = dsu.f(u);
    v = dsu.f(v);
    assert(dsu.join(u, v));
    int root = dsu.f(u);
    int other = root ^ u ^ v;
    res = (res + 1LL * x[root] * x[other]) % mod;
    x[root] = (x[root] + x[other]) % mod;
  };
  vector<vector<pii>> joins(n + 1);
  rep(qq, 0, q) {
    int k, a, b;
    cin >> k >> a >> b;
    if (k) r_dsu.join(a, b, k, f);
    joins[k].emplace_back(a, b);
    cout << res << '\n';
    if (qq == 0 || qq == 1 || qq == 10 || qq == 1000 ||
        qq == 100'000 || qq == q - 1) {
      auto uf = get_rp_dsu(joins, n);
      vi sums(n);
      int offline_ans = 0;
      rep(i, 0, n) {
        int id = uf.f(i);
        offline_ans =
          (offline_ans + 1LL * sums[id] * y[i]) % mod;
        sums[id] = (sums[id] + y[i]) % mod;
      }
      assert(res == offline_ans);
    }
  }
  return 0;
}
