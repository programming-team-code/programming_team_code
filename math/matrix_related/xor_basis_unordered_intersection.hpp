/**
 * @see https://codeforces.com/blog/entry/68953 https://codeforces.com/blog/entry/100066?#comment-887897
 * @code{.cpp}
       basis<int> b;
       basis<ll> b;
       sort(rbegin(b.b), rend(b.b)); //needed for kth smallest walk
 * @endcode
 * notes:
 *     - shrink(v) == shrink(shrink(v))
 *     - for each vector x in b: (bit_floor(x) & shrink(v)) == 0
 *     - for 0 <= i < j < sz(b): (bit_floor(b[i]) & b[j]) == 0
 *     - for 0 <= i < j < sz(b): bit_floor(b[i]) != bit_floor(b[j])
 * @time O(32) or O(64)
 * @space vector 'b' has size O(32) or O(64) at most
 */
template <class T> struct basis {
  vector<T> b;
  T shrink(T v) {
    for (T x : b) v = min(v, v ^ x);
    return v;
  }
  bool insert(T v) {
    return (v = shrink(v)) ? b.push_back(v), 1 : 0;
  }
};
/**
 * @see https://github.com/suisen-cp/cp-library-cpp /blob/main/library/linear_algebra/xor_base.hpp
 * @param u,v 2 xor basis's
 * @returns an xor basis which spans the intersection of the 2 vector spaces spanned by u,v respectively
 * @time O(32^2) or O(64^2); formally O(b^3/w) where b = number of bits, and w is word size
 * @space vector `res` has size O(32) or O(64) at most
 */
template <class T> basis<T> intersection(const basis<T>& u, const basis<T>& v) {
  vector<array<T, 2>> w((int)size(u.b));
  for (int i = 0; i < ((int)size(w)); i++) w[i] = {u.b[i], u.b[i]};
  basis<T> res;
  for (T e : v.b) {
    T s = 0;
    for (auto [x, y] : w)
      if ((e ^ x) < e) e ^= x, s ^= y;
    if (e) w.push_back({e, s});
    else res.insert(s);
  }
  return res;
}
