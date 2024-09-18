#define PROBLEM \
  "https://judge.yosupo.jp/problem/tetration_mod"
#include "../template.hpp"
#include "../../../library/math/totient.hpp"
// trick to remove const so I can use arbitrary prime mode here
#define const ;
#include "../../../library/math/mod_int_pow.hpp"
#undef const
int mod_int_tetration(int b, int e, int local_mod) {
  if (local_mod == 1) return 0;
  if (b == 0) return (e + 1) % 2 % local_mod;
  if (b == 1 || e == 0) return 1;
  if (e == 1) return b % local_mod;
  if (b == 2 && e == 2) return 4 % local_mod;
  if (b == 2 && e == 3) return 16 % local_mod;
  if (b == 3 && e == 2) return 27 % local_mod;
  int t = totient(local_mod);
  int exp = mod_int_tetration(b, e - 1, t);
  mod = local_mod;
  assert(mod != 0);
  return mpow(b, exp + t).x;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int a, b, local_mod;
    cin >> a >> b >> local_mod;
    cout << mod_int_tetration(a, b, local_mod) << '\n';
  }
  return 0;
}
