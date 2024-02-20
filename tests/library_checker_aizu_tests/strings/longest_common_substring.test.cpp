#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array.hpp"
#include "../../../library/strings/suffix_array_related/lcp_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t;
	cin >> s >> t;
	string both = s + '$' + t;
	auto [sa, sa_inv] = get_sa(both, 256);
	vector<int> lcp = get_lcp_array(sa, sa_inv, both);
	array<int, 2> substr_s = {0, 0}, substr_t = {0, 0};
	for (int i = 0; i < ssize(lcp); i++) {
		if (both[sa[i]] == '$' || both[sa[i + 1]] == '$') continue;
		bool before_in_s = (sa[i] < ssize(s));
		bool after_in_s = (sa[i + 1] < ssize(s));
		if (before_in_s ^ after_in_s) {
			if (lcp[i] > substr_s[1] - substr_s[0]) {
				substr_s = {sa[i], sa[i] + lcp[i]};
				substr_t = {sa[i + 1], sa[i + 1] + lcp[i]};
				if (after_in_s) swap(substr_s, substr_t);
				substr_t[0] -= int(ssize(s)) + 1;
				substr_t[1] -= int(ssize(s)) + 1;
			}
		}
	}
	cout << substr_s[0] << " " << substr_s[1] << " " << substr_t[0] << " " << substr_t[1] << '\n';
	return 0;
}
