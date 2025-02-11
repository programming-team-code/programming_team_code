//! https://codeforces.com/blog/entry/68953
//! https://codeforces.com/blog/entry/100066?#comment-887897
//! @code
//!   basis<int> b1;
//!   basis<ll> b2;
//! @endcode
//! b.shrink(v) == b.shrink(b.shrink(v))
//! for x in b.b: (bit_floor(x)&b.shrink(v))==0
//! for 0<=i<j<sz(b.b): (bit_floor(b[i])&b[j])==0
//! @time O(32) or O(64)
//! @space O(32) or O(64)
template<class T> struct basis {
  basic_string<T> b;
  T shrink(T v) {
    for (T x : b) v = min(v, v ^ x);
    return v;
  }
  bool insert(T v) {
    return (v = shrink(v)) ? b += v, 1 : 0;
  }
};
//! https://github.com/suisen-cp/cp-library-cpp/blob/main/library/linear_algebra/xor_base.hpp
//! @time O(32^2) or O(64^2);
//! @space O(32) or O(64)
template<class T>
basis<T> intersection(const basis<T>& u,
  const basis<T>& v) {
  basic_string<array<T, 2>> w;
  for (T e : u.b) w += {e, e};
  basis<T> res;
  for (T e : v.b) {
    T s = 0;
    for (auto [x, y] : w)
      if ((e ^ x) < e) e ^= x, s ^= y;
    if (e) w += {e, s};
    else res.insert(s);
  }
  return res;
}
