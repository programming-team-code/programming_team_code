/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/string /prefix-function.html#implementation
 * @param s string/array
 * @returns prefix function
 * @time O(n)
 * @space this function allocates/returns a O(n) vector
 */
template <class T> vector<int> prefix_function(const T& s) {
  vector<int> pi(sz(s));
  for (int i = 1; i < sz(s); i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    pi[i] = j + (s[i] == s[j]);
  }
  return pi;
}
