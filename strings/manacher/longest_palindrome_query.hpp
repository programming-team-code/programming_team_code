//! @code
//!   RMQ rmq1(a, ranges::min);
//!   RMQ rmq2(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<RMQ<int, function<int(int, int)>>>
//!     rmqs(3, {{}, NULL});
//!   rmqs[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  RMQ(const vector<T>& a, F op): dp(1, a), op(op) {
    for (int i = 0; (2 << i) <= ssize(a); i++) {
      dp.emplace_back(ssize(a) - (2 << i) + 1);
      ranges::transform(dp[i], dp[i] | views::drop(1 << i),
        begin(dp[i + 1]), op);
    }
  }
  T query(int l, int r) {
    assert(l < r);
    int lg = __lg(r - l);
    return op(dp[lg][l], dp[lg][r - (1 << lg)]);
  }
};
//! https://codeforces.com/blog/entry/12143#comment-324162
//! @code
//!   string s;
//!   auto man = manacher(s);
//!   vi s_vec;
//!   auto man1 = manacher(s_vec);
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
vector<int> manacher(const auto& s) {
  int n = ssize(s), p = 0;
  vector<int> man(2 * n - 1);
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
//! queries for longest palindromic substring of a given
//! substring
struct longest_pal_query {
  vector<int> man;
  RMQ<int, function<int(int, int)>> rmq = {{}, NULL};
  //! @param s string/vector
  //! @time O(n log n)
  //! @space O(n log n) for rmq, everything else is O(n)
  longest_pal_query(const auto& s): man(manacher(s)) {
    vector<int> init(ssize(man));
    iota(begin(init), end(init), 0);
    rmq = {init, [&](int i1, int i2) {
             return len(i1) < len(i2) ? i2 : i1;
           }};
  }
  //! @param i center
  //! @returns length of longest palindrome around center
  //! @time O(1)
  //! @space O(1)
  int len(int i) { return i - 2 * man[i] + 1; }
  //! approach: binary search: is there some palindromic
  //! substring with length >= mid ? note for a substring
  //! [l, r) of s, the "relevant" centers are subarray [2
  //! * l, 2 * r - 1) of `man`
  //!
  //! when center i (in "relevant" range) is even (so
  //! represents an odd-length palindrome):
  //!     - i / 2 is index of middle of palindrome
  //!     - l <= i / 2 < r
  //! when center i (in "relevant" range) is odd (so
  //! represents an even-length palindrome):
  //!     - (i - 1) / 2, (i + 1) / 2 are indexes of middles
  //!     of palindrome
  //!     - l <= (i - 1) / 2 < (i + 1) / 2 < r
  //!
  //! @param l,r defines substring [l, r) of s
  //! @returns {start index, length} of longest palindromic
  //! substring of s.substr(l, r - l)
  //!     if there are multiple longest answers, this
  //!     returns an arbitrary start index
  //! @time O(log n)
  //! @space O(1)
  pair<int, int> longest_pal(int l, int r) {
    assert(l < r);
    int pal_len = *ranges::partition_point(
      views::iota(0, r - l), [&](int x) {
        return len(rmq.query(2 * l + x, 2 * r - x - 1)) >
          x;
      });
    int best_center =
      rmq.query(2 * l + pal_len - 1, 2 * r - pal_len);
    return {(best_center + 1 - pal_len) / 2, pal_len};
  }
};
