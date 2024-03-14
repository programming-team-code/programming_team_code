/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/68953 https://codeforces.com/blog/entry/100066?#comment-887897
 * @code{.cpp}
       basis<int> b;
       basis<int64_t> b;
       sort(rbegin(b.b), rend(b.b)); //needed for kth smallest walk
 * @endcode
 * notes:
 *     - shrink(v) == shrink(shrink(v))
 *     - for each vector x in b: (bit_floor(x) & shrink(v)) == 0
 *     - for 0 <= i < j < ssize(b): (bit_floor(b[i]) & b[j]) == 0
 *     - for 0 <= i < j < ssize(b): bit_floor(b[i]) != bit_floor(b[j])
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
