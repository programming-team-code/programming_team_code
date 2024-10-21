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
  int n = ssize(s), p = 0;
  vector<int> man(max(0, 2 * n - 1));
  for (int i = 0; i < 2 * n - 1; i++) {
    int r = i <= 2 * (p - man[p])
      ? p - max(man[2 * p - i], man[p])
      : i / 2;
    man[i] = i - r;
    while (
      man[i] > 0 && r + 1 < n && s[man[i] - 1] == s[r + 1])
      man[i]--, r++, p = i;
  }
  return man;
}
//! @time O(n + q)
//! @space O(n)
template<class T> struct pal_query {
  vector<int> man;
  pal_query(const T& s): man(manacher(s)) {};
  bool is_pal(int l, int r) { // [l, r]
    return man[l + r] <= l;
  }
};
//! https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/manacher.cpp
//! @code
//!   auto r = longest_from_index(pq);
//! @endcode
//! r[i] = max index such that [i, r[i]]
//!   is a palindrome
//! @time O(n)
//! @space O(n)
template<class T>
vector<int> longest_from_index(pal_query<T>& pq) {
  int n = (ssize(pq.man) + 1) / 2;
  vector longest(n, n - 1);
  for (int i = n - 2; i >= 0; i--) {
    longest[i] = min(longest[i + 1] + 1, n - 1);
    while (!pq.is_pal(i, longest[i])) longest[i]--;
  }
  return longest;
}
