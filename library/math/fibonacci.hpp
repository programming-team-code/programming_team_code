#pragma once
const int mod = 998'244'353;
//! https://codeforces.com/blog/entry/14516
//! https://cp-algorithms.com/algebra/fibonacci-numbers.html#fast-doubling-method
//! @code
//!     ll num = fib(n)[0];
//!     //n=0 -> num=0
//!     //n=1 -> num=1
//!     //n=2 -> num=1
//!     //n=3 -> num=2
//!     //n=4 -> num=3
//!     //n=5 -> num=5
//! @endcode
//! @param n an integer
//! @returns a array of {nth fibonacci number, (n+1)th
//! fibonacci number}
//! @time O(log n)
//! @space O(log n) for recursion stack
array<ll, 2> fib(ll n) {
  if (n == 0) return {0LL, 1LL};
  auto [x, y] = fib(n >> 1);
  ll c = x * (2 * y - x + mod) % mod,
     d = (x * x + y * y) % mod;
  if (n & 1) return {d, (c + d) % mod};
  return {c, d};
}
