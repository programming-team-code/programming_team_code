#define PROBLEM \
  "https://judge.yosupo.jp/problem/matrix_product"
// IMO the vector checks && runtime sanitizer (which
// checks index out of bounds) suffices here. All
// the other stuff each slows down the test by 5-10
// seconds, which adds up to a TLE.
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
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) cin >> m1[i][j];
  }
  vector<vector<mi>> m2(m, vector<mi>(k));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) cin >> m2[i][j];
  }
  auto prod = m1 * m2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++)
      cout << prod[i][j] << " ";
    cout << '\n';
  }
  return 0;
}
