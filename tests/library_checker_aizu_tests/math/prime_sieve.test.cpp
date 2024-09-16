#define PROBLEM                                         \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/" \
  "NTL/all/NTL_1_C"
#include "../template.hpp"

#include "../../../kactl/content/number-theory/MillerRabin.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
#include "../../../library/math/prime_sieve/calc_sieve.hpp"
#include "../../../library/math/prime_sieve/is_prime.hpp"
  for (int i = 1; i < sz(sieve); i++)
    assert(isPrime(i) == is_prime(i));
  {
#define sieve linear_sieve
#include "../../../library/math/prime_sieve/calc_linear_sieve.hpp"
#undef sieve
    assert(sieve == linear_sieve);
  }
  int n;
  cin >> n;
  map<int, int> prime_to_max_exponent;
  while (n--) {
    int num;
    cin >> num;
    map<int, int> curr;
    {
      int prev_prime = -1;
#include "../../../library/math/prime_sieve/get_prime_factors.hpp"
      {
        assert(fac >= prev_prime);
        prev_prime = fac;
        curr[fac]++;
      }
    }
    for (auto [p, e] : curr)
      prime_to_max_exponent[p] =
          max(prime_to_max_exponent[p], e);
  }
  int res = 1;
  for (auto [p, e] : prime_to_max_exponent) {
    while (e--) res *= p;
  }
  cout << res << '\n';
  return 0;
}
