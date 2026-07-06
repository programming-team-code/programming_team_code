#define PROBLEM \
  "https://judge.yosupo.jp/problem/matrix_product"
// IMO the vector checks && runtime sanitizer (which checks
// index out of bounds) suffices here. All the other stuff
// each slows down the test by 5-10 seconds, which adds up
// to a TLE.
#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_ASSERTIONS
#include "../template.hpp"
#include "../../../library/math/matrix_related/matrix_mult.hpp"
// NOLINTNEXTLINE(readability-identifier-naming)
const int MOD = 998'244'353;
#include "../../../hackpack-cpp/content/number-theory/ModInt.h"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<mi>> m1(n, vector<mi>(m));
  rep(i, 0, n) rep(j, 0, m) cin >> m1[i][j];
  vector<vector<mi>> m2(m, vector<mi>(k));
  rep(i, 0, m) rep(j, 0, k) cin >> m2[i][j];
  auto prod = m1 * m2;
  rep(i, 0, n) {
    rep(j, 0, k) cout << prod[i][j] << " ";
    cout << '\n';
  }
  return 0;
}
