//! https://codeforces.com/blog/entry/12143#comment-324162
//! @code
//!   auto man = manacher(s);
//! @endcode
//!
//! man[center] = index of start of longest
//!   palindrome centered at `center`
//!
//! center 0 2 4 6 8
//! string b a a b a
//! center  1 3 5 7
//!
//! @time O(n)
//! @space O(n)
template<class T> vector<int> manacher(const T& s) {
  int n = (int)size(s), p = 0;
  vector<int> man(max(0, 2 * n - 1));
  for (int i = 0; i < (2 * n - 1); i++) {
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
//! @time O(n + q)
//! @space O(n)
template<class T> struct pal_query {
  vector<int> man;
  pal_query(const T& s): man(manacher(s)) {};
  bool is_pal(int le, int ri) { // [le, ri]
    return man[le + ri] <= le;
  }
};
//! https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/manacher.cpp
//! @code
//!   auto ri = longest_from_index(pq);
//! @endcode
//! ri[i] = max index such that [i, ri[i]]
//!   is a palindrome
//! @time O(n)
//! @space O(n)
template<class T>
vector<int> longest_from_index(pal_query<T>& pq) {
  int n = ((int)size(pq.man) + 1) / 2;
  vector longest(n, n - 1);
  for (int i = n - 2; i >= 0; i--) {
    longest[i] = min(longest[i + 1] + 1, n - 1);
    while (!pq.is_pal(i, longest[i])) longest[i]--;
  }
  return longest;
}
