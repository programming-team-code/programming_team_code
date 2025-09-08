//! https://cp-algorithms.com/string/prefix-function.html#implementation
//! @time O(n)
//! @space O(n)
vector<int> prefix_function(const auto& s) {
  vector<int> pi(ssize(s));
  for (int i = 1; i < ssize(s); i++) {
    int j = pi[i - 1];
    while (j && s[i] != s[j]) j = pi[j - 1];
    pi[i] = j + (s[i] == s[j]);
  }
  return pi;
}
