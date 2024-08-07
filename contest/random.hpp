mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/**
 * @see https://codeforces.com/blog/entry/61675
 * @code{.cpp}
       mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
       uint64_t x = rng();
       // fixed seed for debugging
       mt19937 rng;
       unsigned x = rng();
       //
       vi a(n);
       shuffle(all(a), rng);
       //
       int x = rnd(0, 1);
       ll x = rnd<ll>(1, 1e18);
 * @endcode
 * @param le,ri defines range [le, ri]
 * @returns random number in range, chosen with probability 1/(ri - le + 1)
 */
template <class T> T rnd(T le, T ri) {
  assert(le <= ri);
  return uniform_int_distribution<T>(le, ri)(rng);
}
