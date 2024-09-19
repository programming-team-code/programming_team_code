#pragma once
//! https://codeforces.com/blog/entry/61675
//! @code
//!   mt19937_64 rng(chrono...);
//!   uint64_t x = rng();
//!   mt19937 rng; // fixed seed for debugging
//!   int x = rnd(0, 1); //random number in [0,1]
//!   ll x = rnd<ll>(1, 1e18);
//! @endcode
mt19937 rng(
  chrono::steady_clock::now().time_since_epoch().count());
template<class T> T rnd(T le, T ri) {
  assert(le <= ri);
  return uniform_int_distribution<T>(le, ri)(rng);
}
