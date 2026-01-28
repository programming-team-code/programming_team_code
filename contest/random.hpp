//! https://codeforces.com/blog/entry/61675
//! @code
//!   //mt19937_64 rng(chrono...);
//!   uint64_t x1 = rng();
//!   mt19937 rng; // fixed seed for debugging
//!   int x2 = rnd(0, 1); //random number in [0,1]
//!   ll x3 = rnd(ll(1), ll(1e18));
//! @endcode
mt19937 rng(
  chrono::steady_clock::now().time_since_epoch().count());
auto rnd(auto l, auto r) {
  assert(l <= r);
  return uniform_int_distribution(l, r)(rng);
}
