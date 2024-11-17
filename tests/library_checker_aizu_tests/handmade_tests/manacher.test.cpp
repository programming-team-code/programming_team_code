#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/strings/manacher/longest_from_index.hpp"
#include "../../../library/strings/manacher/longest_palindrome_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 0; n <= 50; n++) {
    for (int tests = 20; tests--;) {
      string s(n, 'a');
      if (n == 0 || rnd<int>(0, 1) == 0) {
        int mx_char = rnd<int>(0, 5);
        generate(begin(s), end(s), [&]() {
          return char('a' + rnd<int>(0, mx_char));
        });
      } else {
        for (int i = 5; i--;) s[rnd<int>(0, n - 1)] = 'b';
      }
      pal_query pq(s);
      vector<vector<bool>> is_pal_naive(n + 1,
        vector<bool>(n + 1, 1));
      for (int len = 0; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
          int r = l + len;
          if (len >= 2)
            is_pal_naive[l][r] = (s[l] == s[r - 1] &&
              is_pal_naive[l + 1][r - 1]);
        }
      }
      for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
          assert(
            pq.is_pal(i, j) == is_pal_naive[i][j + 1]);
      vector<int> longest(longest_from_index(pq));
      for (int l = 0; l < n; l++) {
        bool seen_pal = 0;
        for (int r = n; r >= l; r--) {
          seen_pal |= is_pal_naive[l][r];
          assert((longest[l] + 1 >= r) == seen_pal);
        }
      }
      vector<vector<int>> count_pals_naive(n + 1,
        vector<int>(n + 1, 0));
      for (int l = 0; l + 1 <= n; l++)
        count_pals_naive[l][l + 1] = 1;
      for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
          int r = l + len;
          count_pals_naive[l][r] = pq.is_pal(l, r - 1) +
            count_pals_naive[l + 1][r] +
            count_pals_naive[l][r - 1] -
            count_pals_naive[l + 1][r - 1];
        }
      }
      vector<vector<int>> longest_pal(n + 1,
        vector<int>(n + 1, 0));
      longest_pal_query lp(s);
      for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
          int r = l + len;
          if (is_pal_naive[l][r]) longest_pal[l][r] = len;
          else
            longest_pal[l][r] = max(longest_pal[l + 1][r],
              longest_pal[l][r - 1]);
          auto [curr_idx, curr_len] = lp.longest_pal(l, r);
          assert(curr_len == longest_pal[l][r]);
          assert(
            pq.is_pal(curr_idx, curr_idx + curr_len - 1));
          assert(l <= curr_idx);
          assert(curr_idx + curr_len <= r);
        }
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
