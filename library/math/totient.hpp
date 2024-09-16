//! @file
#pragma once
//! @param n an integer
//! @returns number of integers x (1<=x<=n) such that gcd(x,
//! n) = 1
//! @time O(sqrt n) but can be improved with Pollard-rho
//! @space O(1)
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
