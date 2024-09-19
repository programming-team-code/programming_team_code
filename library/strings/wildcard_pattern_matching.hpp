#pragma once
//! https://codeforces.com/blog/entry/111380
//! @code
//!   auto match = wildcard_pattern_matching(
//!     haystack, needle, conv);
//! @endcode
//! haystack[match[i],sz(needle)) == needle
//! haystack[i]=0 or needle[i]=0 for a wildcard
//! @time O((n+m) log (n+m))
//! @space O(n+m)
template<class T> vector<T> make_powers(const T& v) {
  int n = sz(v);
  vector pws(3, T(n));
  rep(i, 0, n) {
    pws[0][i] = v[i];
    pws[1][i] = v[i] * v[i];
    pws[2][i] = v[i] * v[i] * v[i];
  }
  return pws;
}
template<class T, class F>
vector<bool> wildcard_pattern_matching(const T& haystack,
  const T& needle, const F& conv) {
  int n = sz(haystack), m = sz(needle);
  auto haystack_pws = make_powers(haystack);
  auto needle_pws = make_powers(needle);
  for (auto& needle_pw : needle_pws) reverse(all(needle_pw));
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
