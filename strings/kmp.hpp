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
//! @code
//!   string s,t;
//!   KMP kmp(t);
//!   auto match = kmp.find_str(s);
//!   vi s_vec,t_vec;
//!   KMP kmp1(t_vec);
//!   auto match2 = kmp1.find_str(s_vec);
//! @endcode
//! if match[i] == 1 then s[i,sz(t)) == t
//! @time O(|s| + |t|)
//! @space O(|s| + |t|)
template<class T> struct KMP {
  T t;
  vector<int> pi;
  KMP(const T& t): t(t), pi(prefix_function(t)) {}
  vector<bool> find_str(const T& s) {
    vector<bool> is_m(ssize(s));
    int j = 0;
    for (int i = 0; i < ssize(s); i++) {
      while (j && s[i] != t[j]) j = pi[j - 1];
      j += (s[i] == t[j]);
      if (j == ssize(t)) {
        is_m[i - j + 1] = 1;
        j = pi[j - 1];
      }
    }
    return is_m;
  }
};
