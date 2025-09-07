#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"
#include "../template.hpp"
#define const ;
#include "../../../library/math/mod_division.hpp"
#undef const
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (mod = 1; mod < 500; mod++) {
    for (int x = 0; x < mod; x++) {
      for (int y = 0; y < mod; y++) {
        if (gcd(y, mod) == 1) {
          int quotient = mod_div(x, y);
          assert(1LL * quotient * y % mod == x);
        }
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
