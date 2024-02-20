/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @see https://codeforces.com/blog/entry/14516 https://cp-algorithms.com/algebra /fibonacci-numbers.html#fast-doubling-method
 * @code{.cpp}
       auto val = fib(n)[0];
       //n=0 -> val=0
       //n=1 -> val=1
       //n=2 -> val=1
       //n=3 -> val=2
       //n=4 -> val=3
       //n=5 -> val=5
 * @endcode
 * @param n an integer
 * @returns a array of {nth fibonacci number, (n+1)th fibonacci number}
 * @time O(log n)
 * @space O(log n) for recursion stack
 */
array<int64_t, 2> fib(int64_t n) {
	if (n == 0) return {0LL, 1LL};
	auto [x, y] = fib(n >> 1);
	auto c = x * (2 * y - x + mod) % mod, d = (x * x + y * y) % mod;
	if (n & 1) return {d, (c + d) % mod};
	return {c, d};
}
