#pragma once
//! https://cp-algorithms.com/string/prefix-function.html#implementation
//! @time O(n)
//! @space O(n)
vi prefix_function(const auto& s) {
  vi pi(sz(s));
  rep(i, 1, sz(s)) {
    int j = pi[i - 1];
    while (j && s[i] != s[j]) j = pi[j - 1];
    pi[i] = j + (s[i] == s[j]);
  }
  return pi;
}
