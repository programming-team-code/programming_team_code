//! @file
#pragma once
/**
 * @see https://cp-algorithms.com/string /prefix-function.html#implementation
 * @param s string/array
 * @returns prefix function
 * @time O(n)
 * @space this function allocates/returns a O(n) vector
 */
template <class T> vi prefix_function(const T& s) {
  vi pi(sz(s));
  rep(i, 1, sz(s)) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    pi[i] = j + (s[i] == s[j]);
  }
  return pi;
}
