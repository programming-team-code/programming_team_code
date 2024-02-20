#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/manacher/longest_from_index.hpp"
#include "../../../library/strings/manacher/count_palindromes_query.hpp"
#include "../../../library/strings/manacher/longest_palindrome_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int n = 0; n <= 50; n++) {
		for (int tests = 20; tests--;) {
			string s(n, 'a');
			if (n == 0 || get_rand<int>(0, 1) == 0) {
				int mx_char = get_rand<int>(0, 5);
				generate(begin(s), end(s), [&]() {return char('a' + get_rand<int>(0, mx_char));});
			} else {
				for (int i = 5; i--;)
					s[get_rand<int>(0, n - 1)] = 'b';
			}
			vector<int> man = manacher(s);
			vector<vector<bool>> is_pal_naive(n + 1, vector<bool>(n + 1, 1));
			for (int len = 0; len <= n; len++) {
				for (int le = 0; le + len <= n; le++) {
					int ri = le + len;
					if (len >= 2)
						is_pal_naive[le][ri] = (s[le] == s[ri - 1] && is_pal_naive[le + 1][ri - 1]);
					assert(is_pal(man, le, ri) == is_pal_naive[le][ri]);
				}
			}
			vector<int> longest(longest_from_index(man));
			for (int le = 0; le < n; le++) {
				bool seen_pal = 0;
				for (int ri = n; ri >= le; ri--) {
					seen_pal |= is_pal_naive[le][ri];
					assert((le + longest[le] >= ri) == seen_pal);
				}
			}
			vector<vector<int>> count_pals_naive(n + 1, vector<int>(n + 1, 0));
			for (int le = 0; le + 1 <= n; le++) count_pals_naive[le][le + 1] = 1;
			for (int len = 2; len <= n; len++) {
				for (int le = 0; le + len <= n; le++) {
					int ri = le + len;
					count_pals_naive[le][ri] = is_pal(man, le, ri) + count_pals_naive[le + 1][ri] + count_pals_naive[le][ri - 1] - count_pals_naive[le + 1][ri - 1];
				}
			}
			count_pal_query pcq(s);
			for (int len = 1; len <= n; len++) {
				for (int le = 0; le + len <= n; le++) {
					int ri = le + len;
					auto curr = pcq.count_pals(le, ri);
					assert(curr == count_pals_naive[le][ri]);
				}
			}
			vector<vector<int>> longest_pal(n + 1, vector<int>(n + 1, 0));
			longest_pal_query lp(s);
			for (int len = 1; len <= n; len++) {
				for (int le = 0; le + len <= n; le++) {
					int ri = le + len;
					if (is_pal_naive[le][ri])
						longest_pal[le][ri] = len;
					else
						longest_pal[le][ri] = max(longest_pal[le + 1][ri], longest_pal[le][ri - 1]);
					auto [curr_idx, curr_len] = lp.longest_pal(le, ri);
					assert(curr_len == longest_pal[le][ri]);
					assert(is_pal(man, curr_idx, curr_idx + curr_len));
					assert(le <= curr_idx);
					assert(curr_idx + curr_len <= ri);
				}
			}
		}
	}
	cout << "Hello World\n";
	return 0;
}
