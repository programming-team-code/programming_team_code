/**
 * @param n an integer
 * @returns number of integers x (1<=x<=n) such that gcd(x, n) = 1
 * @time O(sqrt n) but can be improved with Pollard-rho
 * @space O(1)
 */
int totient(int n) {
  int res = n;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      res -= res / i;
    }
  if (n > 1) res -= res / n;
  return res;
}
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/number-theory/ModPow.h
 * @param b base
 * @param e exponent
 * @param mod modulo
 * @returns (b^e)%mod, 1 for 0^0.
 * @time O(log e)
 * @space O(1)
 */
int64_t bin_exp(int64_t b, int64_t e, int mod) {
  assert(0 <= e);
  int64_t res = 1;
  if ((b %= mod) < 0) b += mod;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) res = res * b % mod;
  return res;
}
/**
 * @see https://cp-algorithms.com/algebra /phi-function.html#generalization
 *
 * Let t = totient(mod).
 * If log2(mod) <= e then (b^e)%mod == (b^(t+(e%t)))%mod
 * So you need enough base cases to cover when log2(mod) > e
 *
 * @param b,e,mod see return
 * @returns b ^ (b ^ (b ^ ... )) % mod, where the height of the tower
 * is e.
 * @time O(sqrt(mod) * log(mod))
 * @space O(log(mod)) for recursion stack, since totient(totient(mod)) <= mod/2
 */
int64_t tetration(int64_t b, int64_t e, int mod) {
  if (mod == 1) return 0;
  if (b == 0) return (e + 1) % 2 % mod;
  if (b == 1 || e == 0) return 1;
  if (e == 1) return b % mod;
  if (b == 2 && e == 2) return 4 % mod;
  if (b == 2 && e == 3) return 16 % mod;
  if (b == 3 && e == 2) return 27 % mod;
  int t = totient(mod);
  int64_t exp = tetration(b, e - 1, t);
  return bin_exp(b, exp + t, mod);
}
