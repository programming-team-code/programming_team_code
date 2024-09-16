//! @file
#pragma once
template <class T> vector<T> make_powers(const T& v) {
  int n = sz(v);
  vector pws(3, T(n));
  rep(i, 0, n) {
    pws[0][i] = v[i];
    pws[1][i] = v[i] * v[i];
    pws[2][i] = v[i] * v[i] * v[i];
  }
  return pws;
}
//! @brief wildcard pattern matching
//! @note the cumulative values for comparision will be on
//! the order of (max element)^4
//!
//! @param haystack is the string|array|vector to search in
//! where the value `0` represents a wildcard
//! @param needle is the string|array|vector to search for
//! @param conv is the convolution, typically supported by
//! an implementation of NTT or FFT
//!
//! @return a vector of booleans where the value at index
//! `i` is `true` if the needle is found starting at index
//! `i` in the haystack
//!
//! @time O(max(n,m) log(max(n,m))) where n is the size of
//! the haystack and m is the size of the needle
template <class T, class F>
vector<bool> wildcard_pattern_matching(const T& haystack,
                                       const T& needle,
                                       const F& conv) {
  int n = sz(haystack), m = sz(needle);
  auto haystack_pws = make_powers(haystack);
  auto needle_pws = make_powers(needle);
  for (auto& needle_pw : needle_pws)
    reverse(all(needle_pw));
  vector<T> res(3);
  rep(pw_hay, 0, 3) res[pw_hay] =
      conv(haystack_pws[pw_hay], needle_pws[2 - pw_hay]);
  vector<bool> matches(n - m + 1);
  rep(i, 0, n - m + 1) {
    int id = i + m - 1;
    auto num = res[0][id] - 2 * res[1][id] + res[2][id];
    matches[i] = num == 0;
  }
  return matches;
}
