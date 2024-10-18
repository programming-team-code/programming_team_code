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
