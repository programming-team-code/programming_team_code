#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"
#include "../template.hpp"
// trick to remove const so I can use arbitrary prime mode
// here
#define const ;
#include "../../../library/math/mod_int_pow.hpp"
#undef const
int main() {
  cin.tie(0)->sync_with_stdio(0);
  mod = 1'000'000'007;
  int m, n;
  cin >> m >> n;
  cout << mpow(m, n).x << '\n';
  return 0;
}
