#define PROBLEM "https://judge.yosupo.jp/problem/prefix_substring_lcs"
#include "../template.hpp"

#include "../../../library/strings/longest_common_subsequence/lcs_dp.hpp"
#include "../../../library/data_structures/wavelet_merge/wavelet_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q;
	string s, t;
	cin >> q >> s >> t;
	vector<wavelet_tree> wts;
	{
		lcs_dp lcs(t);
		wts.emplace_back(lcs.dp, -1, ssize(t));
		for (char c : s) {
			lcs.push_onto_s(c);
			{
				vector<bool> seen(ssize(t));
				for (int i = 0; i < ssize(t); i++) {
					int val = lcs.dp[i];
					assert(val <= i);
					if (val == -1) continue;
					assert(!seen[val]);
					seen[val] = 1;
				}
			}
			wts.emplace_back(lcs.dp, -1, ssize(t));
		}
	}
	for (int i = 0; i < q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		cout << wts[a].rect_count(b, c, -1, b) << '\n';
	}
	return 0;
}
