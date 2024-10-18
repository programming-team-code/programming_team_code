//! https://cp-algorithms.com/string/prefix-function.html#implementation
//! @time O(n)
//! @space O(n)
template<class T> vector<int> prefix_function(const T& s) {
  vector<int> pi((int)size(s));
  for (int i = 1; i < ((int)size(s)); i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    pi[i] = j + (s[i] == s[j]);
  }
  return pi;
}
//! @code
//!   KMP kmp(t);
//!   auto match = kmp.find_str(s);
//! @endcode
//! s[match[i],sz(t)) == t
//! @time O(|s| + |t|)
//! @space O(|s| + |t|)
template<class T> struct KMP {
  T t;
  vector<int> pi;
  KMP(const T& a_t): t(a_t), pi(prefix_function(t)) {}
  vector<int> find_str(const T& s) {
    vector<int> matches;
    int j = 0;
    for (int i = 0; i < ((int)size(s)); i++) {
      while (j > 0 && t[j] != s[i]) j = pi[j - 1];
      j += (t[j] == s[i]);
      if (j == (int)size(t)) {
        matches.push_back(i - (int)size(t) + 1);
        j = pi[j - 1];
      }
    }
    return matches;
  }
};
