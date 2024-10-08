//! https://codeforces.com/blog/entry/14516
//! https://cp-algorithms.com/algebra/fibonacci-numbers.html#fast-doubling-method
//! @code
//!   ll num = fib(n)[0];
//!   //n=0 -> num=0
//!   //n=1 -> num=1
//!   //n=2 -> num=1
//!   //n=3 -> num=2
//!   //n=4 -> num=3
//! @endcode
//! @time O(log n)
//! @space O(log n)
const int mod = 998'244'353;
array<int64_t, 2> fib(int64_t n) {
  if (n == 0) return {0LL, 1LL};
  auto [x, y] = fib(n >> 1);
  int64_t c = x * (2 * y - x + mod) % mod,
          d = (x * x + y * y) % mod;
  if (n & 1) return {d, (c + d) % mod};
  return {c, d};
}
