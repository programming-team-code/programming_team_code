//! @file
#pragma once
//! @see
//! https://codeforces.com/blog/entry/12143#comment-324162
//!
//! subarray [le, ri] has "center" i = le + ri
//!
//! center 0 2 4 6 8
//! string b a a b a
//! center  1 3 5 7
//!
//! man = {0, 1, 1, 0, 2, 3, 2, 4, 4}
//!
//! for "center" `i`, man[i] stores minimum index `le` such
//! that [le, i - le] is a palindrome
//!
//! @param s string/vector
//! @returns see above
//! @time O(n)
//! @space a O(n) vector is allocated and returned
template <class T> vi manacher(const T& s) {
  int n = sz(s), p = 0;
  vi man(max(0, 2 * n - 1));
  rep(i, 0, 2 * n - 1) {
    int ri = i <= 2 * (p - man[p])
                 ? p - max(man[2 * p - i], man[p])
                 : i / 2;
    man[i] = i - ri;
    while (man[i] > 0 && ri + 1 < n &&
           s[man[i] - 1] == s[ri + 1])
      man[i]--, ri++, p = i;
  }
  return man;
}
