/**
 * @see https://codeforces.com/blog/entry/12143#comment-324162
 *
 * subarray [le, ri] has "center" i = le + ri
 *
 * center 0 2 4 6 8
 * string b a a b a
 * center  1 3 5 7
 *
 * man = {0, 1, 1, 0, 2, 3, 2, 4, 4}
 *
 * for "center" `i`, man[i] stores minimum index `le` such that [le, i - le] is a palindrome
 *
 * @param s string/vector
 * @returns see above
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T> vector<int> manacher(const T& s) {
  int n = (int)size(s), p = 0;
  vector<int> man(max(0, 2 * n - 1));
  for (int i = 0; i < (2 * n - 1); i++) {
    int ri = i <= 2 * (p - man[p]) ? p - max(man[2 * p - i], man[p]) : i / 2;
    man[i] = i - ri;
    while (man[i] > 0 && ri + 1 < n && s[man[i] - 1] == s[ri + 1])
      man[i]--, ri++, p = i;
  }
  return man;
}
template <class T> struct pal_query {
  int n;
  vector<int> man;
  pal_query(const T& s) : n((int)size(s)), man(manacher(s)){};
  /**
   * @param le,ri defines substring [le,ri]
   * @returns 1 iff s.substr(le, ri - le + 1) is a palindrome
   * @time O(1)
   * @space O(1)
   */
  bool is_pal(int le, int ri) {
    return man[le + ri] <= le;
  }
};
/**
 * @see https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Strings/manacher.cpp
 *
 * @param pq palindrome query struct
 * @returns ri[i] = max index such that [i, ri[i]] is a palindrome
 * @time O(n)
 * @space an O(n) vector is allocated and returned
 */
template <class T> vector<int> longest_from_index(pal_query<T>& pq) {
  int n = ((int)size(pq.man) + 1) / 2;
  vector longest(n, n - 1);
  for (int i = n - 2; i >= 0; i--) {
    longest[i] = min(longest[i + 1] + 1, n - 1);
    while (!pq.is_pal(i, longest[i])) longest[i]--;
  }
  return longest;
}
