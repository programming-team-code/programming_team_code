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
